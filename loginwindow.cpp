#include "loginwindow.h"
#include "database.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(400, 300);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setAlignment(Qt::AlignCenter);
    
    // Título
    QLabel *titleLabel = new QLabel("Iniciar Sesión", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");
    
    // Campos de entrada
    QLabel *apodoLabel = new QLabel("Apodo:", this);
    apodoEdit = new QLineEdit(this);
    apodoEdit->setPlaceholderText("Ingresa tu apodo");
    
    QLabel *passwordLabel = new QLabel("Contraseña:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Ingresa tu contraseña");
    
    // Botones
    loginButton = new QPushButton("Iniciar Sesión", this);
    loginButton->setStyleSheet("QPushButton { padding: 10px; font-size: 14px; }");
    
    registroButton = new QPushButton("¿No tienes cuenta? Regístrate", this);
    registroButton->setStyleSheet("QPushButton { padding: 8px; font-size: 12px; color: blue; border: none; }");
    
    // Agregar al layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(apodoLabel);
    mainLayout->addWidget(apodoEdit);
    mainLayout->addWidget(passwordLabel);
    mainLayout->addWidget(passwordEdit);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(registroButton);
    
    // Conectar señales
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::intentarLogin);
    connect(registroButton, &QPushButton::clicked, this, &LoginWindow::irARegistro);
    connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginWindow::intentarLogin);
}

void LoginWindow::intentarLogin()
{
    QString apodo = apodoEdit->text().trimmed();
    QString password = passwordEdit->text();
    
    if (apodo.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor, completa todos los campos.");
        return;
    }
    
    if (Database::instance().validarLogin(apodo, password)) {
        // Limpiar campos
        apodoEdit->clear();
        passwordEdit->clear();
        
        emit loginExitoso(apodo);
    } else {
        QMessageBox::warning(this, "Error", "Apodo o contraseña incorrectos.");
        passwordEdit->clear();
    }
}

void LoginWindow::irARegistro()
{
    // Limpiar campos antes de cambiar de ventana
    apodoEdit->clear();
    passwordEdit->clear();
    
    emit mostrarRegistro();
}
