#ifndef RUTINASWINDOW_H
#define RUTINASWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTextEdit>
#include <QScrollArea>
#include <QMap>
#include <QStringList>
#include "database.h"

class RutinasWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit RutinasWindow(QWidget *parent = nullptr);
    void cargarUsuario(const QString& apodo);
    
signals:
    void cerrarSesion();
    
private slots:
    void cerrarSesionSlot();
    void generarNuevaRutina();
    
private:
    void setupUI();
    void mostrarRutinas(const QMap<QString, QStringList>& rutinas);
    void mostrarInfoUsuario(const Usuario& usuario);
    
    QLabel *bienvenidaLabel;
    QLabel *infoUsuarioLabel;
    QTabWidget *tabWidget;
    QPushButton *nuevaRutinaButton;
    QPushButton *cerrarSesionButton;
    
    QString usuarioActual;
    Usuario datosUsuario;
};

#endif // RUTINASWINDOW_H
