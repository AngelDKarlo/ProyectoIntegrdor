#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "loginwindow.h"
#include "registerwindow.h"
#include "rutinaswindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void mostrarRegistro();
    void mostrarLogin();
    void mostrarRutinas(const QString& apodo);
    
private:
    QStackedWidget *stackedWidget;
    LoginWindow *loginWindow;
    RegisterWindow *registerWindow;
    RutinasWindow *rutinasWindow;
};

#endif // MAINWINDOW_H
