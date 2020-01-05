/**
 * @file mainwindow.h
 * @brief MainWindow header.
 * @author Erick Andres Obregon Fonseca.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>
#include "socketcliente.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief Constructor.
     * @param parent - pointer of QWidget object.
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief Destructor.
     */
    ~MainWindow();

private:
    //! Socket for client connection.
    SocketCliente *connection;
    //! @brief Gui object.
    Ui::MainWindow *ui;

private slots:
    /**
     * @brief Management of the message recived on Sockets.
     * @param instruction
     */
    void show_msj(QString instruction);
    /**
     * @brief Answer to client to notify that node was deleted.
     */
    void send_del();
    /**
     * @brief Send to client the solicited node.
     */
    void send_get();
    /**
     * @brief Answer to client to notify that node was added.
     */
    void send_new();
};

#endif // MAINWINDOW_H
