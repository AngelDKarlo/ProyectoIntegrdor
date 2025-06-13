#include "rutinaswindow.h"
#include "rutinagenerator.h"
#include <QMessageBox>

RutinasWindow::RutinasWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void RutinasWindow::setupUI()
{
    setFixedSize(800, 600);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Header con información del usuario
    QHBoxLayout *headerLayout = new QHBoxLayout();
    
    bienvenidaLabel = new QLabel("Bienvenido", this);
    bienvenidaLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2E7D32;");
    
    cerrarSesionButton = new QPushButton("Cerrar Sesión", this);
    cerrarSesionButton->setStyleSheet("QPushButton { padding: 8px 16px; background-color: #f44336; color: white; border: none; border-radius: 4px; }");
    
    headerLayout->addWidget(bienvenidaLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(cerrarSesionButton);
    
    // Información del usuario
    infoUsuarioLabel = new QLabel(this);
    infoUsuarioLabel->setStyleSheet("padding: 10px; background-color: #f5f5f5; border-radius: 5px; margin-bottom: 10px;");
    infoUsuarioLabel->setWordWrap(true);
    
    // Botón para generar nueva rutina
    nuevaRutinaButton = new QPushButton("Generar Nueva Rutina", this);
    nuevaRutinaButton->setStyleSheet("QPushButton { padding: 10px; font-size: 14px; background-color: #4CAF50; color: white; border: none; border-radius: 5px; }");
    
    // Tabs para los días de la semana
    tabWidget = new QTabWidget(this);
    tabWidget->setStyleSheet("QTabWidget::pane { border: 1px solid #ccc; } QTabBar::tab { padding: 8px 16px; margin-right: 2px; } QTabBar::tab:selected { background-color: #4CAF50; color: white; }");
    
    // Agregar todo al layout
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(infoUsuarioLabel);
    mainLayout->addWidget(nuevaRutinaButton);
    mainLayout->addWidget(tabWidget);
    
    // Conectar señales
    connect(cerrarSesionButton, &QPushButton::clicked, this, &RutinasWindow::cerrarSesionSlot);
    connect(nuevaRutinaButton, &QPushButton::clicked, this, &RutinasWindow::generarNuevaRutina);
}

void RutinasWindow::cargarUsuario(const QString& apodo)
{
    usuarioActual = apodo;
    datosUsuario = Database::instance().obtenerUsuario(apodo);
    
    // Actualizar bienvenida
    bienvenidaLabel->setText(QString("¡Hola, %1!").arg(datosUsuario.nombre.isEmpty() ? apodo : datosUsuario.nombre));
    
    // Mostrar información del usuario
    mostrarInfoUsuario(datosUsuario);
    
    // Generar y mostrar rutinas
    QMap<QString, QStringList> rutinas = RutinaGenerator::generarRutinaSemanal(datosUsuario);
    mostrarRutinas(rutinas);
}

void RutinasWindow::mostrarInfoUsuario(const Usuario& usuario)
{
    QString info = QString(
        "<b>Perfil del Usuario</b><br>"
        "Edad: %1 años | Peso: %2 kg | Estatura: %3 m<br>"
        "Nivel: %4 | Objetivo: %5<br>"
        "Estado de ánimo: %6 | Mascotas: %7"
    ).arg(usuario.edad)
     .arg(usuario.peso)
     .arg(usuario.estatura)
     .arg(usuario.nivelGimnasio)
     .arg(usuario.objetivo)
     .arg(usuario.estadoAnimo)
     .arg(usuario.tieneMascotas ? "Sí" : "No");
    
    infoUsuarioLabel->setText(info);
}

void RutinasWindow::mostrarRutinas(const QMap<QString, QStringList>& rutinas)
{
    // Limpiar tabs existentes
    tabWidget->clear();
    
    QStringList diasSemana = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
    
    for (const QString& dia : diasSemana) {
        if (rutinas.contains(dia)) {
            QScrollArea *scrollArea = new QScrollArea();
            scrollArea->setWidgetResizable(true);
            
            QWidget *contentWidget = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout(contentWidget);
            layout->setSpacing(10);
            layout->setContentsMargins(15, 15, 15, 15);
            
            QStringList ejercicios = rutinas[dia];
            
            if (ejercicios.isEmpty() || (ejercicios.size() == 1 && ejercicios.first().contains("Descanso"))) {
                // Día de descanso
                QLabel *descansoLabel = new QLabel(ejercicios.isEmpty() ? "Día de descanso" : ejercicios.first());
                descansoLabel->setAlignment(Qt::AlignCenter);
                descansoLabel->setStyleSheet("font-size: 16px; color: #666; padding: 20px;");
                layout->addWidget(descansoLabel);
            } else {
                // Día con ejercicios
                QLabel *tituloLabel = new QLabel(QString("Rutina para %1").arg(dia));
                tituloLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2E7D32; margin-bottom: 10px;");
                layout->addWidget(tituloLabel);
                
                for (int i = 0; i < ejercicios.size(); ++i) {
                    QLabel *ejercicioLabel = new QLabel(QString("%1. %2").arg(i + 1).arg(ejercicios[i]));
                    ejercicioLabel->setStyleSheet("padding: 8px; background-color: white; border: 1px solid #ddd; border-radius: 4px; margin-bottom: 5px;");
                    ejercicioLabel->setWordWrap(true);
                    layout->addWidget(ejercicioLabel);
                }
            }
            
            layout->addStretch();
            scrollArea->setWidget(contentWidget);
            tabWidget->addTab(scrollArea, dia);
        }
    }
}

void RutinasWindow::cerrarSesionSlot()
{
    // Limpiar datos
    usuarioActual.clear();
    datosUsuario = Usuario();
    tabWidget->clear();
    
    emit cerrarSesion();
}

void RutinasWindow::generarNuevaRutina()
{
    if (usuarioActual.isEmpty()) {
        QMessageBox::warning(this, "Error", "No hay usuario cargado.");
        return;
    }
    
    // Generar nueva rutina
    QMap<QString, QStringList> nuevasRutinas = RutinaGenerator::generarRutinaSemanal(datosUsuario);
    mostrarRutinas(nuevasRutinas);
    
    QMessageBox::information(this, "Rutina Actualizada", "¡Se ha generado una nueva rutina personalizada para ti!");
}
