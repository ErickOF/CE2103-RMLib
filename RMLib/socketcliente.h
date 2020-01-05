/**
 * @file socketcliente.h
 * @brief Contains a set of methods for handling Socket connection.
 * @author Erick Andres Obregon Fonseca.
 */
#ifndef SOCKETCLIENTE_H
#define SOCKETCLIENTE_H

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <pthread.h>
#include <QObject>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

/**
 * @brief The SocketCliente class.
 */
class SocketCliente: public QObject{
    Q_OBJECT
public:
    /**
     * @brief Constructor.
     */
    SocketCliente(int portA, int portB, string ipA, string ipB);
    /**
     * @brief Destructor.
     */
    ~SocketCliente();
    /**
     * @brief Connect the SocketClient with Server.
     * @return
     */
    bool connect_socket();
    /**
     * @brief Send messages to Server.
     * @param msj - message to send.
     */
    void set_msj(const char* msj);

private:
    //! @brief Client identifier's.
    int descriptor;
    //! @brief Information about socket & connections types.
    sockaddr_in info;
    //! Port of Active Server.
    int portA;
    //! Port of Pasive Server.
    int portB;
    /**
     * @brief Control the server connection.
     * @param obj - server to connected.
     * @return
     */
    static void* controlator(void* obj);

signals:
    /**
     * @brief Signal when a new message is recived.
     * @param msj - recived message.
     */
    void new_msg(QString msj);
};

#endif // SOCKETCLIENTE_H
