#include "mainwindow.h"
#include "ui_mainwindow.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connection = new SocketCliente(4050, 4051, "127.0.0.1", "127.0.0.1");
    // Verificar que se realizo la conexion
    if (!connection->connect_socket()){
        QMessageBox::critical(this, "Error", "No se puede realizar la conexion con el servidor", QMessageBox::Ok);
    } // Crear conexiones entre clases
    connect(connection, SIGNAL(new_msg(QString)), this, SLOT(show_msj(QString)));
    connect(ui->btn_enviar, SIGNAL(clicked()), this, SLOT(send_new()));
    connect(ui->btn_obtener, SIGNAL(clicked()), this, SLOT(send_get()));
    connect(ui->btn_eliminar, SIGNAL(clicked()), this, SLOT(send_del()));
}

// Destructor
MainWindow::~MainWindow() {
    delete ui;
}

// Manejar la respuesta que se recibe
void MainWindow::show_msj(QString instruction){
    string msj = instruction.toStdString();
    // Extraer la accion
    string command = msj.substr(0, 3);
    if (command == "new"){
        int mid = msj.find("~");
        // Obtener la llave y la informacion
        string key = msj.substr(3, mid - 3);
        string data = msj.substr(mid + 1, msj.find("¬") - mid - 1);
    } else if (command == "get"){
        int mid = msj.find("~");
        // Obtener la llave y la informacion
        string key = msj.substr(3, mid - 3);
        string data = msj.substr(mid + 1, msj.find("¬") - mid - 1);
        // Mostrar la informacion del nodo obtenido
        string to_show = "Informacion en la llave " + key + " es " + data;
        QMessageBox::information(this, "Informacion del nodo", to_show.c_str(), QMessageBox::Ok);
    } else if (command == "del"){
        int mid = msj.find("~");
        string key = msj.substr(3, mid - 3);
    } else if (command == "syn"){
        cout << "Sincronizando ";
    } else if (command == "act"){
        cout << "Verificando" << endl;
    } // Acciones erroneas
    else if (command == "nad"){
        QMessageBox::warning(this, "Error", "Elemento ya existe", QMessageBox::Ok);
    } else if (command == "nex"){
        QMessageBox::warning(this, "Error", "Elemento no existe", QMessageBox::Ok);
    }
}

// Enviar peticion para eliminar
void MainWindow::send_del(){
    bool ok;
    // Pedir los datos
    QString key = QInputDialog::getText(this, tr("Llave"), tr("Ingrese la llave:"), QLineEdit::Normal, "", &ok);
    if (ok) {
        // Enviar mensaje al servidor
        string msj = "del" + key.toStdString() + "~";
        connection->set_msj(msj.c_str());
    } else {
        QMessageBox::warning(this, "Error", "Llave no ingresada correctamente", QMessageBox::Ok);
    }
}

// Enviar peticion para obtener
void MainWindow::send_get(){
    bool ok;
    // Pedir los datos
    QString key = QInputDialog::getText(this, tr("Llave"), tr("Ingrese la llave:"), QLineEdit::Normal, "", &ok);
    if (ok) {
        // Enviar mensaje al servidor
        string msj = "get" + key.toStdString() + "~";
        connection->set_msj(msj.c_str());
    } else {
        QMessageBox::warning(this, "Error", "Llave no ingresada correctamente", QMessageBox::Ok);
    }
}

// Enviar peticion para crear nuevo
void MainWindow::send_new() {
    bool ok1, ok2;
    QString key, data;
    // Pedir informacion
    key = QInputDialog::getText(this, tr("Llave"), tr("Ingrese la llave:"), QLineEdit::Normal, "", &ok1);
    data = QInputDialog::getText(this, tr("Informacion"), tr("Ingrese la informacion:"), QLineEdit::Normal, "", &ok2);
    if (ok1 && ok2) {
        // Enviar mensaje al servidor
        string msj = "new" + key.toStdString() + "~" + data.toStdString() + "¬";
        connection->set_msj(msj.c_str());
    } else{
        QMessageBox::warning(this, "Error", "Datos no ingresados correctamente", QMessageBox::Ok);
    }
}
