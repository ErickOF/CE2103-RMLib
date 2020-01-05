#include "mainwindow.h"
#include "ui_mainwindow.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // Crear hilo para correr el servidor
    pthread_t thread_server, thread_check;
    pthread_create(&thread_server, 0, MainWindow::run_server, SocketServer::get_instance());
    // Crear el hilo del verificador de referencias
    pthread_detach(thread_server);
    Memory *memory = SocketServer::get_instance()->get_memory();
    pthread_create(&thread_check, 0, SocketServer::check_reference_count, memory);
    pthread_detach(thread_check);
    // Conectar entre clases
    connect(SocketServer::get_instance(), SIGNAL(update()), this, SLOT(update_gui()));
}

// Destructor
MainWindow::~MainWindow() {
    delete ui;
}

// Actualizar GUI
void MainWindow::update_gui(){
    Memory *list_memory = SocketServer::get_instance()->get_memory();
    Cache *list_cache = SocketServer::get_instance()->get_cache();
    // Limpiar la lista
    ui->listaMemoria->clear();
    ui->listaCache->clear();
    NodeMemory *nodem = NULL;
    // Recorrer la lista
    for (int i = 0; i < list_memory->get_size(); ++i) {
        nodem = list_memory->get(i);
        // Agregar elemento a la lista
        QString label = QString::fromStdString("{" + nodem->get_key() + ":" + nodem->get_data() + "}");
        ui->listaMemoria->addItem(label);
    }
    nodem = NULL;
    list_memory = NULL;
    delete list_memory;
    delete nodem;
    NodeCache *nodec = NULL;
    for (int i = 0; i < list_cache->get_size(); ++i) {
        nodec = list_cache->get(i);
        // Agregar elemento a la lista
        QString label = QString::fromStdString(nodec->get_key() + ":" + nodec->get_data());
        ui->listaCache->addItem(label);
    }
    list_cache = NULL;
    nodec = NULL;
    delete nodec;
    delete list_cache;
}

// Correr servidor
void* MainWindow::run_server(void* obj){
    SocketServer *server = (SocketServer*)obj;
    emit server->run();
    return NULL;
}
