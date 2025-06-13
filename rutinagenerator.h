#ifndef RUTINAGENERATOR_H
#define RUTINAGENERATOR_H

#include <QString>
#include <QStringList>
#include <QMap>
#include "database.h"

struct Ejercicio {
    QString nombre;
    QString grupoMuscular;
    QString nivel; // basico, intermedio, avanzado
    int series;
    QString repeticiones;
};

class RutinaGenerator
{
public:
    static QMap<QString, QStringList> generarRutinaSemanal(const Usuario& usuario);
    
private:
    static QList<Ejercicio> obtenerEjercicios();
    static QList<Ejercicio> filtrarPorNivel(const QList<Ejercicio>& ejercicios, const QString& nivel);
    static QList<Ejercicio> filtrarPorGrupoMuscular(const QList<Ejercicio>& ejercicios, const QString& grupo);
    static QStringList crearRutinaDia(const QList<Ejercicio>& ejercicios, int cantidad);
    static QStringList getDiasPorObjetivo(const QString& objetivo);
};

#endif // RUTINAGENERATOR_H
