#include "socketcliente.h"

// Constructor
SocketCliente::SocketCliente(int portA, int portB, string ipA, string ipB){
    this->portA = portA;
    this->portB = portB;
}

// Destructor
SocketCliente::~SocketCliente(){
}

// Conectar con el servidor
bool SocketCliente::connect_socket(){
    // Obtener el descriptor
    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // Verificar si ocurrio un error
    if (descriptor < 0) return false;
    // Llenar la estructura de la informacion de la conexion
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr("127.0.0.1");// Local host;
    info.sin_port = ntohs(portA);
    memset(&info.sin_zero, 0, sizeof(info.sin_zero));
    // Verificar la conexion
    if(::connect(descriptor, (sockaddr*)&info, (socklen_t)sizeof(info)) < 0) return false;
    // Crear hilo para escuchar
    pthread_t hilo;
    pthread_create(&hilo, 0, SocketCliente::controlator, (void*)this);
    pthread_detach(hilo);
    return true;
}

// Socket que controla conexion
void* SocketCliente::controlator(void *obj){
    SocketCliente *padre = (SocketCliente*)obj;
    // Crear puntero al objeto que se recive
    while (true){
        string msj;
        while (true){
            char buffer[10] = {0};
            // Ir leyendo lo que llega
            int bytes_leidos = recv(padre->descriptor, buffer, 10, 0);
            msj.append(buffer, bytes_leidos);
            // Verificar si el cliente esta conectado
            if (bytes_leidos <= 0){
                close(padre->descriptor);
                pthread_exit(NULL);
            } // Verificar que termino de leer
            if (bytes_leidos < 10) {
                emit padre->new_msg(QString::fromStdString(msj));
                break;
            }
        }
    }
    close(padre->descriptor);
    pthread_exit(NULL);
}

// Enviar el mensaje
void SocketCliente::set_msj(const char* msj){
    send(descriptor, msj, strlen(msj), 0);
}
