#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Gym App");
    setFixedSize(800, 600);
    
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    // Crear ventanas
    loginWindow = new LoginWindow(this);
    registerWindow = new RegisterWindow(this);
    rutinasWindow = new RutinasWindow(this);
    
    // Agregar al stack
    stackedWidget->addWidget(loginWindow);
    stackedWidget->addWidget(registerWindow);
    stackedWidget->addWidget(rutinasWindow);
    
    // Conectar señales
    connect(loginWindow, &LoginWindow::mostrarRegistro, this, &MainWindow::mostrarRegistro);
    connect(loginWindow, &LoginWindow::loginExitoso, this, &MainWindow::mostrarRutinas);
    connect(registerWindow, &RegisterWindow::mostrarLogin, this, &MainWindow::mostrarLogin);
    connect(rutinasWindow, &RutinasWindow::cerrarSesion, this, &MainWindow::mostrarLogin);
    
    // Mostrar login por defecto
    stackedWidget->setCurrentWidget(loginWindow);
}

MainWindow::~MainWindow()
{
}

void MainWindow::mostrarRegistro()
{
    stackedWidget->setCurrentWidget(registerWindow);
}

void MainWindow::mostrarLogin()
{
    stackedWidget->setCurrentWidget(loginWindow);
}

void MainWindow::mostrarRutinas(const QString& apodo)
{
    rutinasWindow->cargarUsuario(apodo);
    stackedWidget->setCurrentWidget(rutinasWindow);
}
