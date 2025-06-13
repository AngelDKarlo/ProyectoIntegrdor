#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>

class RegisterWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    
signals:
    void mostrarLogin();
    
private slots:
    void registrarUsuario();
    void volverALogin();
    
private:
    void setupUI();
    void limpiarCampos();
    
    QLineEdit *nombreEdit;
    QDoubleSpinBox *pesoSpinBox;
    QSpinBox *edadSpinBox;
    QDoubleSpinBox *estaturaSpinBox;
    QComboBox *nivelComboBox;
    QLineEdit *apodoEdit;
    QComboBox *estadoAnimoComboBox;
    QComboBox *objetivoComboBox;
    QCheckBox *mascotasCheckBox;
    QLineEdit *passwordEdit;
    QLineEdit *confirmarPasswordEdit;
    QPushButton *registrarButton;
    QPushButton *volverButton;
};

#endif // REGISTERWINDOW_H
