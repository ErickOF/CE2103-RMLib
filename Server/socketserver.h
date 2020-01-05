/**
 * @file socketcliente.h
 * @brief Contains a set of methods for handling Socket connection.
 * @author Erick Andres Obregon Fonseca.
 */

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

/**
 * @brief Maximun connections.
 */
#define MAX 5

#include <arpa/inet.h>
#include "cache.h"
#include <chrono>
#include <iostream>
#include "memory.h"
#include <netdb.h>
#include <pthread.h>
#include <QObject>
#include <QString>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

/**
 * @brief The DataSocket struct.
 */
struct DataSocket {
    /**
     * @brief identifier.
     */
    int descriptor;
    /**
     * @brief information.
     */
    sockaddr_in info;
};

/**
 * @brief The SocketServer class.
 */
class SocketServer: public QObject{
    Q_OBJECT
public:
    /**
     * @brief Check if the reference count of a node has reached 0.
     * @param obj - memory to check.
     */
    static void* check_reference_count(void* obj);
    /**
     * @brief Return memory.
     * @return memory.
     */
    Cache* get_cache();
    /**
     * @brief Return a static instance of this class.
     * @return static instance of this class.
     */
    static SocketServer* get_instance();
    /**
     * @brief Return memory.
     * @return memory.
     */
    Memory* get_memory();
    /**
     * @brief Run server.
     */
    void run();
    /**
     * @brief Constructor.
     */
    explicit SocketServer(QObject *parent = 0);
    /**
     * @brief Destructor.
     */
    ~SocketServer();

private:
    //! @brief Cache
    Cache *cache;
    //! @brief All connected clients.
    vector<int> clients;
    //! @brief Client identifier's.
    int descriptor;
    //! @brief Information about socket & connections types.
    sockaddr_in info;
    //! @brief Memory.
    Memory *memory;
    /**
     * @brief Control the cliente connection.
     * @param obj - client to connected.
     * @return
     */
    static void* client_controlator(void* obj);
    /**
     * @brief Create socket connection.
     * @return true or false if connection was succesfull.
     */
    bool create_socket();
    /**
     * @brief Link socket with kernell.
     * @return true or false if connection was succesfull.
     */
    bool link_kernell();
    /**
     * @brief Called it when a client send a request.
     * @param msj - request.
     * @param client - cliente who sends the request.
     */
    void new_instruction(string msj, DataSocket *client);

signals:
    /**
     * @brief Signal to update the gui.
     */
    void update();
};

#endif // SOCKETSERVER_H
