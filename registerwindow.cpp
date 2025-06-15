#include "registerwindow.h"
#include "database.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void RegisterWindow::setupUI()
{
    setFixedSize(500, 650);
    
    // Crear scroll area para el contenido
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(500, 650);
    
    QWidget *contentWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setSpacing(15);
    
    // Título
    QLabel *titleLabel = new QLabel("Registro de Usuario", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 20px;");
    
    // Crear grid layout para los campos
    QGridLayout *formLayout = new QGridLayout();
    formLayout->setSpacing(10);
    
    int row = 0;
    
    // Nombre
    formLayout->addWidget(new QLabel("Nombre completo:"), row, 0);
    nombreEdit = new QLineEdit();
    nombreEdit->setPlaceholderText("Ej: Juan Pérez");
    formLayout->addWidget(nombreEdit, row++, 1);
    
    // Peso
    formLayout->addWidget(new QLabel("Peso (kg):"), row, 0);
    pesoSpinBox = new QDoubleSpinBox();
    pesoSpinBox->setRange(30.0, 200.0);
    pesoSpinBox->setValue(70.0);
    pesoSpinBox->setSuffix(" kg");
    formLayout->addWidget(pesoSpinBox, row++, 1);
    
    // Edad
    formLayout->addWidget(new QLabel("Edad:"), row, 0);
    edadSpinBox = new QSpinBox();
    edadSpinBox->setRange(16, 100);
    edadSpinBox->setValue(25);
    edadSpinBox->setSuffix(" años");
    formLayout->addWidget(edadSpinBox, row++, 1);
    
    // Estatura
    formLayout->addWidget(new QLabel("Estatura (m):"), row, 0);
    estaturaSpinBox = new QDoubleSpinBox();
    estaturaSpinBox->setRange(1.40, 2.20);
    estaturaSpinBox->setValue(1.70);
    estaturaSpinBox->setDecimals(2);
    estaturaSpinBox->setSuffix(" m");
    formLayout->addWidget(estaturaSpinBox, row++, 1);
    
    // Nivel de gimnasio
    formLayout->addWidget(new QLabel("Nivel de gimnasio:"), row, 0);
    nivelComboBox = new QComboBox();
    nivelComboBox->addItems({"basico", "intermedio", "avanzado"});
    formLayout->addWidget(nivelComboBox, row++, 1);
    
    // Apodo
    formLayout->addWidget(new QLabel("Apodo (usuario):"), row, 0);
    apodoEdit = new QLineEdit();
    apodoEdit->setPlaceholderText("Nombre de usuario único");
    formLayout->addWidget(apodoEdit, row++, 1);
    
    // Estado de ánimo
    formLayout->addWidget(new QLabel("Estado de ánimo:"), row, 0);
    estadoAnimoComboBox = new QComboBox();
    estadoAnimoComboBox->addItems({"Motivado", "Relajado", "Energético", "Determinado", "Tranquilo"});
    formLayout->addWidget(estadoAnimoComboBox, row++, 1);
    
    // Objetivo - ACTUALIZADO con opciones más específicas
    formLayout->addWidget(new QLabel("Objetivo principal:"), row, 0);
    objetivoComboBox = new QComboBox();
    objetivoComboBox->addItems({
        "Ganar músculo",        // Hipertrofia: 5-6 ejercicios, 2 compuestos + 3-4 accesorios
        "Ganar peso",          // Fuerza: 3-5 ejercicios, 1-2 principales + 2-3 auxiliares  
        "Perder peso",         // Pérdida de grasa: 4-5 ejercicios + cardio
        "Mantener estado físico" // Resistencia: 4-6 ejercicios, 1 por grupo muscular
    });
    
    // Agregar tooltips para explicar cada objetivo
    objetivoComboBox->setToolTip(
        "• Ganar músculo: Rutinas de hipertrofia con mayor volumen\n"
        "• Ganar peso: Rutinas de fuerza con ejercicios básicos\n"
        "• Perder peso: Combinación de pesas y cardio\n"
        "• Mantener estado físico: Rutinas balanceadas de resistencia"
    );
    
    formLayout->addWidget(objetivoComboBox, row++, 1);
    
    // Mascotas
    formLayout->addWidget(new QLabel("¿Tienes mascotas?"), row, 0);
    mascotasCheckBox = new QCheckBox("Sí, tengo mascotas");
    mascotasCheckBox->setToolTip("Las rutinas incluirán sugerencias para actividades con mascotas en días de descanso");
    formLayout->addWidget(mascotasCheckBox, row++, 1);
    
    // Contraseña
    formLayout->addWidget(new QLabel("Contraseña:"), row, 0);
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Mínimo 6 caracteres");
    formLayout->addWidget(passwordEdit, row++, 1);
    
    // Confirmar contraseña
    formLayout->addWidget(new QLabel("Confirmar contraseña:"), row, 0);
    confirmarPasswordEdit = new QLineEdit();
    confirmarPasswordEdit->setEchoMode(QLineEdit::Password);
    confirmarPasswordEdit->setPlaceholderText("Repite la contraseña");
    formLayout->addWidget(confirmarPasswordEdit, row++, 1);
    
    // Info adicional sobre los objetivos
    QLabel *infoLabel = new QLabel(
        "<b>Información sobre objetivos:</b><br>"
        "🏋️ <b>Ganar músculo:</b> Rutinas de hipertrofia, 5-6 ejercicios por día<br>"
        "💪 <b>Ganar peso:</b> Rutinas de fuerza, ejercicios básicos pesados<br>"
        "🔥 <b>Perder peso:</b> Combinación pesas + cardio, formato circuito<br>"
        "⚖️ <b>Mantener estado:</b> Rutinas balanceadas, todos los grupos musculares"
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #f0f8ff; padding: 10px; border-radius: 5px; font-size: 11px;");
    
    // Botones
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    registrarButton = new QPushButton("Registrarse");
    registrarButton->setStyleSheet("QPushButton { padding: 10px; font-size: 14px; background-color: #4CAF50; color: white; border: none; border-radius: 5px; }");
    
    volverButton = new QPushButton("Volver al Login");
    volverButton->setStyleSheet("QPushButton { padding: 10px; font-size: 14px; background-color: #f44336; color: white; border: none; border-radius: 5px; }");
    
    buttonLayout->addWidget(volverButton);
    buttonLayout->addWidget(registrarButton);
    
    // Agregar todo al layout principal
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    
    scrollArea->setWidget(contentWidget);
    
    // Conectar señales
    connect(registrarButton, &QPushButton::clicked, this, &RegisterWindow::registrarUsuario);
    connect(volverButton, &QPushButton::clicked, this, &RegisterWindow::volverALogin);
}

void RegisterWindow::registrarUsuario()
{
    // Validar campos
    if (nombreEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "El nombre no puede estar vacío.");
        return;
    }
    
    if (apodoEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "El apodo no puede estar vacío.");
        return;
    }
    
    if (passwordEdit->text().length() < 6) {
        QMessageBox::warning(this, "Error", "La contraseña debe tener al menos 6 caracteres.");
        return;
    }
    
    if (passwordEdit->text() != confirmarPasswordEdit->text()) {
        QMessageBox::warning(this, "Error", "Las contraseñas no coinciden.");
        return;
    }
    
    // Crear usuario
    Usuario usuario;
    usuario.nombre = nombreEdit->text().trimmed();
    usuario.peso = pesoSpinBox->value();
    usuario.edad = edadSpinBox->value();
    usuario.estatura = estaturaSpinBox->value();
    usuario.nivelGimnasio = nivelComboBox->currentText();
    usuario.apodo = apodoEdit->text().trimmed();
    usuario.estadoAnimo = estadoAnimoComboBox->currentText();
    usuario.objetivo = objetivoComboBox->currentText();
    usuario.tieneMascotas = mascotasCheckBox->isChecked();
    usuario.password = passwordEdit->text();
    
    // Intentar registrar
    if (Database::instance().registrarUsuario(usuario)) {
        QString mensaje = QString(
            "¡Usuario registrado correctamente!\n\n"
            "Tu rutina será optimizada para: %1\n"
            "Nivel: %2\n\n"
            "¡Ahora puedes iniciar sesión!"
        ).arg(usuario.objetivo).arg(usuario.nivelGimnasio);
        
        QMessageBox::information(this, "¡Bienvenido al Gym!", mensaje);
        limpiarCampos();
        emit mostrarLogin();
    } else {
        QMessageBox::warning(this, "Error", "No se pudo registrar el usuario.\nEl apodo puede estar ya en uso.");
    }
}

void RegisterWindow::volverALogin()
{
    limpiarCampos();
    emit mostrarLogin();
}

void RegisterWindow::limpiarCampos()
{
    nombreEdit->clear();
    pesoSpinBox->setValue(70.0);
    edadSpinBox->setValue(25);
    estaturaSpinBox->setValue(1.70);
    nivelComboBox->setCurrentIndex(0);
    apodoEdit->clear();
    estadoAnimoComboBox->setCurrentIndex(0);
    objetivoComboBox->setCurrentIndex(0);
    mascotasCheckBox->setChecked(false);
    passwordEdit->clear();
    confirmarPasswordEdit->clear();
}
