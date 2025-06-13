#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class LoginWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit LoginWindow(QWidget *parent = nullptr);
    
signals:
    void mostrarRegistro();
    void loginExitoso(const QString& apodo);
    
private slots:
    void intentarLogin();
    void irARegistro();
    
private:
    QLineEdit *apodoEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registroButton;
};

#endif // LOGINWINDOW_H
