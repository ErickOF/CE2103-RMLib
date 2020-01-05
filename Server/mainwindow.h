/**
 * @file mainwindow.h
 * @brief MainWindow header.
 * @author Erick Andres Obregon Fonseca.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "socketserver.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class.
 */
class MainWindow : public QMainWindow{
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
    //! @brief Gui object.
    Ui::MainWindow *ui;
    /**
     * @brief Run server
     * @param obj
     */
    static void* run_server(void* obj);
    //! Socket for connection
    SocketServer *server;

private slots:
    /**
     * @brief Update the gui.
     */
    void update_gui();
};
#endif // MAINWINDOW_H
