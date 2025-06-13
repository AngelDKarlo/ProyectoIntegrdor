#include <QApplication>
#include "mainwindow.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Inicializar base de datos
    Database::instance().initializeDatabase();
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
