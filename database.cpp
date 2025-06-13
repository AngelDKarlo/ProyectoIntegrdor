#include "database.h"
#include <QDebug>
#include <QCryptographicHash>

Database& Database::instance()
{
    static Database instance;
    return instance;
}

bool Database::initializeDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("gym_app.db");
    
    if (!db.open()) {
        qDebug() << "Error al abrir la base de datos:" << db.lastError().text();
        return false;
    }
    
    return createTables();
}

bool Database::createTables()
{
    QSqlQuery query;
    QString createTable = R"(
        CREATE TABLE IF NOT EXISTS usuarios (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL,
            peso REAL NOT NULL,
            edad INTEGER NOT NULL,
            estatura REAL NOT NULL,
            nivel_gimnasio TEXT NOT NULL,
            apodo TEXT UNIQUE NOT NULL,
            estado_animo TEXT NOT NULL,
            objetivo TEXT NOT NULL,
            tiene_mascotas INTEGER NOT NULL,
            password TEXT NOT NULL
        )
    )";
    
    if (!query.exec(createTable)) {
        qDebug() << "Error al crear tabla usuarios:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool Database::registrarUsuario(const Usuario& usuario)
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO usuarios (nombre, peso, edad, estatura, nivel_gimnasio, 
                             apodo, estado_animo, objetivo, tiene_mascotas, password)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    )");
    
    // Encriptar contraseña
    QByteArray hashedPassword = QCryptographicHash::hash(usuario.password.toUtf8(), 
                                                        QCryptographicHash::Sha256);
    
    query.addBindValue(usuario.nombre);
    query.addBindValue(usuario.peso);
    query.addBindValue(usuario.edad);
    query.addBindValue(usuario.estatura);
    query.addBindValue(usuario.nivelGimnasio);
    query.addBindValue(usuario.apodo);
    query.addBindValue(usuario.estadoAnimo);
    query.addBindValue(usuario.objetivo);
    query.addBindValue(usuario.tieneMascotas ? 1 : 0);
    query.addBindValue(QString(hashedPassword.toHex()));
    
    if (!query.exec()) {
        qDebug() << "Error al registrar usuario:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool Database::validarLogin(const QString& apodo, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM usuarios WHERE apodo = ?");
    query.addBindValue(apodo);
    
    if (!query.exec() || !query.next()) {
        return false;
    }
    
    QString storedPassword = query.value(0).toString();
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), 
                                                        QCryptographicHash::Sha256);
    
    return storedPassword == QString(hashedPassword.toHex());
}

Usuario Database::obtenerUsuario(const QString& apodo)
{
    Usuario usuario;
    QSqlQuery query;
    query.prepare(R"(
        SELECT nombre, peso, edad, estatura, nivel_gimnasio, apodo, 
               estado_animo, objetivo, tiene_mascotas
        FROM usuarios WHERE apodo = ?
    )");
    query.addBindValue(apodo);
    
    if (query.exec() && query.next()) {
        usuario.nombre = query.value(0).toString();
        usuario.peso = query.value(1).toDouble();
        usuario.edad = query.value(2).toInt();
        usuario.estatura = query.value(3).toDouble();
        usuario.nivelGimnasio = query.value(4).toString();
        usuario.apodo = query.value(5).toString();
        usuario.estadoAnimo = query.value(6).toString();
        usuario.objetivo = query.value(7).toString();
        usuario.tieneMascotas = query.value(8).toBool();
    }
    
    return usuario;
}
