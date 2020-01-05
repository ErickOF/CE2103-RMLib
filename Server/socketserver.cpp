#include "socketserver.h"

// Constructor
SocketServer::SocketServer(QObject *parent):
    QObject(parent){
    cache = new Cache;
    memory = new Memory;
}

// Destructor
SocketServer::~SocketServer(){
}

// Verifica si el conteo de referencia de un nodo ha llegado a 0
void* SocketServer::check_reference_count(void *obj){
    Memory *remote_memory = (Memory*)obj;
    NodeMemory* node = NULL;
    string msj;
    //Ejecutar para siempre
    while (true){
        // Recorrer los elementos en memory
        for (int i = 0; i < remote_memory->get_size(); ++i) {
            node = remote_memory->get(i);
            // Decrementar el conteo de referencia
            node->decrease_count();
            // Verificar si el conteo de ese elemento llego a 0 y eliminarlo
            if (node->get_count() == 0){
                msj = "del" + node->get_key() + "~";
                node = NULL;
                SocketServer::get_instance()->new_instruction(msj, new DataSocket);
            }
        } // Dormir thread
        this_thread::sleep_for(chrono::seconds(1));
    }
    node = NULL;
    delete node;
    return NULL;
}

// Controla los clientes que se conectan
void* SocketServer::client_controlator(void* obj){
    // Crear puntero al objeto que se recive
    DataSocket *data = (DataSocket*) obj;
    string msj;
    while (true){
        while (true){
            char buffer[200] = {0};
            // Ir leyendo lo que llega
            int bytes_leidos = recv(data->descriptor, buffer, 200, 0);
            msj.append(buffer, bytes_leidos);
            // Verificar si el cliente esta conectado
            if (bytes_leidos <= 0){
                close(data->descriptor);
                pthread_exit(NULL);
                break;
            } // Verificar que termino de leer
            if (bytes_leidos <= 200) {
                try{
                    cout << "Error" << endl;
                    SocketServer::get_instance()->new_instruction(msj, data);
                    cout << "send";
                } catch (...) {
                    cout << "Error";
                } msj = "";
                break;
            }
        }
    }
    close(data->descriptor);
    data = NULL;
    delete data;
}

// Crear el socket del servidor
bool SocketServer::create_socket(){
    // Obtener el descriptor
    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // Verificar si ocurrio un error
    if (descriptor < 0) return false;
    // Llenar la estructura de la informacion de la conexion
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = INADDR_ANY;
    info.sin_port = htons(4050);
    memset(&info.sin_zero, 0, sizeof(info.sin_zero));
    return true;
}

// Obtener el cache
Cache* SocketServer::get_cache(){
    return cache;
}

// Singleton
SocketServer* SocketServer::get_instance(){
    static SocketServer server;
    return &server;
}

// Obtener la memoria
Memory *SocketServer::get_memory(){
    return memory;
}

// Ligar con el kernell
bool SocketServer::link_kernell(){
    if (bind(descriptor, (sockaddr*) &info, (socklen_t)sizeof(info)) < 0) return false;
    listen(descriptor, MAX);
    return true;
}

// Manejar las instrucciones que llegan de los clientes
void SocketServer::new_instruction(string msj, DataSocket* client){
    // Obtener la accion
    int mid;
    string key, data, msj2;
    string command = msj.substr(0, 3);
    msj2 = msj;
    cout << command << endl;
    if (command == "new"){
        mid = msj.find("~");
        key = msj.substr(3, mid - 3);
        // Si no existe se agrega y se le notifica al cliente
        cout << "4";
        if (!memory->exist(key)){
            cout << "5";
            memory->add(data, key);
            cout << "6";
            cache->add(data, key);
            cout << "7";
            const char* answer = msj.c_str();
            cout << "8";
            send(client->descriptor, answer, strlen(answer), 0);
            cout << "9";
            delete answer;
            cout << "a";
        } else{
            cout << "b";
            send(client->descriptor, "nad", strlen("nad"), 0);
        }
        cout << "c";
    } else if (command == "get"){
        int mid = msj.find("~");
        // Obtener llave
        string key = msj.substr(3, mid - 3);
        // Obtener elemento y enviarlo al cliente
        if (cache->exist(key)){
            NodeCache* node = cache->get(key);
            const char answer = *(msj + node->get_data() + "¬").c_str();
            send(client->descriptor, &answer, strlen(&answer), 0);
            node = NULL;
            delete node;
        } else if (memory->exist(key)){
            NodeMemory* node = memory->get(key);
            const char answer = *(msj + node->get_data() + "¬").c_str();
            send(client->descriptor, &answer, strlen(&answer), 0);
            node = NULL;
            delete node;
        }else{
            send(client->descriptor, "nex", strlen("nex"), 0);
        }
    } else if (command == "del"){
        int mid = msj.find("~");
        // Obtener llave
        string key = msj.substr(3, mid - 3);
        // Eliminar el elemento y notificar al cliente
        if (memory->exist(key)) {
            memory->remove(key);
            if (cache->exist(key)) cache->remove(key);
            send(client->descriptor, msj.c_str(), strlen(msj.c_str()), 0);
        } else {
            send(client->descriptor, "nex", strlen("nex"), 0);
        }
    } else if (command == "syn"){
        cout << "Sincronizando ";
    } else if (command == "act"){
        cout << "Verificando" << endl;
    } else {
        cout << "None" << endl;
    }
    cout << "Ready" << endl;
    SocketServer *server = SocketServer::get_instance();
    cout << "server got" << endl;
    emit server->update();
    cout << "update" << endl;
    server = NULL;
    delete server;
    cout << "server delete" << endl;
}

// Correr servidor
void SocketServer::run(){
    if (!create_socket()) throw string("Error al crear el socket");
    if (!link_kernell()) throw string("Error al ligar kernell");
    // Esperar a los clientes
    while (true){
        //
        DataSocket data;
        socklen_t tam = sizeof(data.info);
        data.descriptor = accept(descriptor, (sockaddr *) &data.info, &tam);
        // Verificar si se acepto la conexion
        if (data.descriptor < 0) cout << "Error al aceptar la conexion" << endl;
        else {
            // Agregar cliente
            clients.push_back(data.descriptor);
            // Crear hilo
            pthread_t hilo;
            pthread_create(&hilo, 0, SocketServer::client_controlator, (void*)&data);
            pthread_detach(hilo);
            cout << "Agregado";
        }
    } close(descriptor);
}
