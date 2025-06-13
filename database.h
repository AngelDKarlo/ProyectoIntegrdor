#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>

struct Usuario {
    QString nombre;
    double peso;
    int edad;
    double estatura;
    QString nivelGimnasio;
    QString apodo;
    QString estadoAnimo;
    QString objetivo;
    bool tieneMascotas;
    QString password;
};

class Database
{
public:
    static Database& instance();
    bool initializeDatabase();
    bool registrarUsuario(const Usuario& usuario);
    bool validarLogin(const QString& apodo, const QString& password);
    Usuario obtenerUsuario(const QString& apodo);
    
private:
    Database() = default;
    QSqlDatabase db;
    bool createTables();
};

#endif // DATABASE_H
