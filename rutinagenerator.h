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
    QString tipo; // compuesto, accesorio, cardio
    int series;
    QString repeticiones;
    QString descripcion;
};

class RutinaGenerator
{
public:
    static QMap<QString, QStringList> generarRutinaSemanal(const Usuario& usuario);
    
private:
    static QList<Ejercicio> obtenerEjercicios();
    static QList<Ejercicio> filtrarPorNivel(const QList<Ejercicio>& ejercicios, const QString& nivel);
    static QList<Ejercicio> filtrarPorGrupoMuscular(const QList<Ejercicio>& ejercicios, const QString& grupo);
    static QList<Ejercicio> filtrarPorTipo(const QList<Ejercicio>& ejercicios, const QString& tipo);
    static QStringList crearRutinaDia(const QList<Ejercicio>& ejercicios, const QString& objetivo, const QString& nivel);
    static QStringList getDiasPorObjetivo(const QString& objetivo);
    static QStringList getGruposMuscularesPorObjetivo(const QString& objetivo);
    
    // Nuevas funciones para objetivos específicos
    static QStringList crearRutinaHipertrofia(const QList<Ejercicio>& ejercicios, const QString& grupoMuscular, const QString& nivel);
    static QStringList crearRutinaFuerza(const QList<Ejercicio>& ejercicios, const QString& grupoMuscular, const QString& nivel);
    static QStringList crearRutinaResistencia(const QList<Ejercicio>& ejercicios, const QString& nivel);
    static QStringList crearRutinaPerdidaGrasa(const QList<Ejercicio>& ejercicios, const QString& grupoMuscular, const QString& nivel);
};

#endif // RUTINAGENERATOR_H
