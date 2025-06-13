#include "rutinagenerator.h"
#include <QRandomGenerator>

QMap<QString, QStringList> RutinaGenerator::generarRutinaSemanal(const Usuario& usuario)
{
    QMap<QString, QStringList> rutinaSemanal;
    QList<Ejercicio> todosEjercicios = obtenerEjercicios();
    QList<Ejercicio> ejerciciosFiltrados = filtrarPorNivel(todosEjercicios, usuario.nivelGimnasio);
    
    QStringList diasActivos = getDiasPorObjetivo(usuario.objetivo);
    QStringList todosDias = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
    
    // Definir grupos musculares por día
    QStringList gruposMusculares;
    if (usuario.objetivo == "Ganar músculo") {
        gruposMusculares = {"Pecho", "Espalda", "Piernas", "Brazos", "Hombros"};
    } else if (usuario.objetivo == "Perder peso") {
        gruposMusculares = {"Cardio", "Pecho", "Piernas", "Cardio", "Espalda"};
    } else {
        gruposMusculares = {"Pecho", "Piernas", "Espalda", "Brazos"};
    }
    
    int diaIndex = 0;
    for (const QString& dia : todosDias) {
        if (diasActivos.contains(dia) && diaIndex < gruposMusculares.size()) {
            QString grupo = gruposMusculares[diaIndex];
            QList<Ejercicio> ejerciciosGrupo = filtrarPorGrupoMuscular(ejerciciosFiltrados, grupo);
            
            int cantidadEjercicios = (usuario.nivelGimnasio == "basico") ? 4 : 
                                   (usuario.nivelGimnasio == "intermedio") ? 6 : 8;
            
            rutinaSemanal[dia] = crearRutinaDia(ejerciciosGrupo, cantidadEjercicios);
            diaIndex++;
        } else {
            rutinaSemanal[dia] = QStringList() << "Día de descanso - ¡Recupera tu energía!";
        }
    }
    
    return rutinaSemanal;
}

QList<Ejercicio> RutinaGenerator::obtenerEjercicios()
{
    QList<Ejercicio> ejercicios;
    
    // Ejercicios de Pecho
    ejercicios << Ejercicio{"Press de banca", "Pecho", "basico", 3, "8-12"};
    ejercicios << Ejercicio{"Flexiones", "Pecho", "basico", 3, "10-15"};
    ejercicios << Ejercicio{"Press inclinado con mancuernas", "Pecho", "intermedio", 4, "8-10"};
    ejercicios << Ejercicio{"Aperturas con mancuernas", "Pecho", "intermedio", 3, "10-12"};
    ejercicios << Ejercicio{"Press declinado", "Pecho", "avanzado", 4, "6-8"};
    ejercicios << Ejercicio{"Dips en paralelas", "Pecho", "avanzado", 3, "8-12"};
    
    // Ejercicios de Espalda
    ejercicios << Ejercicio{"Dominadas asistidas", "Espalda", "basico", 3, "5-8"};
    ejercicios << Ejercicio{"Remo con mancuerna", "Espalda", "basico", 3, "8-12"};
    ejercicios << Ejercicio{"Jalones al pecho", "Espalda", "intermedio", 4, "8-10"};
    ejercicios << Ejercicio{"Remo en polea baja", "Espalda", "intermedio", 3, "10-12"};
    ejercicios << Ejercicio{"Dominadas", "Espalda", "avanzado", 4, "5-10"};
    ejercicios << Ejercicio{"Peso muerto", "Espalda", "avanzado", 4, "6-8"};
    
    // Ejercicios de Piernas
    ejercicios << Ejercicio{"Sentadillas", "Piernas", "basico", 3, "12-15"};
    ejercicios << Ejercicio{"Prensa de piernas", "Piernas", "basico", 3, "10-12"};
    ejercicios << Ejercicio{"Zancadas", "Piernas", "intermedio", 3, "10-12 cada pierna"};
    ejercicios << Ejercicio{"Extensiones de cuádriceps", "Piernas", "intermedio", 3, "12-15"};
    ejercicios << Ejercicio{"Sentadilla búlgara", "Piernas", "avanzado", 4, "8-10 cada pierna"};
    ejercicios << Ejercicio{"Peso muerto rumano", "Piernas", "avanzado", 4, "8-10"};
    
    // Ejercicios de Brazos
    ejercicios << Ejercicio{"Curl de bíceps", "Brazos", "basico", 3, "10-12"};
    ejercicios << Ejercicio{"Extensiones de tríceps", "Brazos", "basico", 3, "10-12"};
    ejercicios << Ejercicio{"Curl martillo", "Brazos", "intermedio", 3, "8-10"};
    ejercicios << Ejercicio{"Dips en banco", "Brazos", "intermedio", 3, "8-12"};
    ejercicios << Ejercicio{"Curl con barra", "Brazos", "avanzado", 4, "6-8"};
    ejercicios << Ejercicio{"Press francés", "Brazos", "avanzado", 4, "8-10"};
    
    // Ejercicios de Hombros
    ejercicios << Ejercicio{"Press militar con mancuernas", "Hombros", "basico", 3, "8-10"};
    ejercicios << Ejercicio{"Elevaciones laterales", "Hombros", "basico", 3, "10-12"};
    ejercicios << Ejercicio{"Elevaciones frontales", "Hombros", "intermedio", 3, "10-12"};
    ejercicios << Ejercicio{"Remo al mentón", "Hombros", "intermedio", 3, "8-10"};
    ejercicios << Ejercicio{"Press militar con barra", "Hombros", "avanzado", 4, "6-8"};
    ejercicios << Ejercicio{"Elevaciones posteriores", "Hombros", "avanzado", 3, "10-12"};
    
    // Ejercicios de Cardio
    ejercicios << Ejercicio{"Caminata rápida", "Cardio", "basico", 1, "20-30 min"};
    ejercicios << Ejercicio{"Bicicleta estática", "Cardio", "basico", 1, "15-25 min"};
    ejercicios << Ejercicio{"Elíptica", "Cardio", "intermedio", 1, "20-30 min"};
    ejercicios << Ejercicio{"Intervalos en cinta", "Cardio", "intermedio", 1, "15-20 min"};
    ejercicios << Ejercicio{"Burpees", "Cardio", "avanzado", 3, "10-15"};
    ejercicios << Ejercicio{"Mountain climbers", "Cardio", "avanzado", 3, "30-45 seg"};
    
    return ejercicios;
}

QList<Ejercicio> RutinaGenerator::filtrarPorNivel(const QList<Ejercicio>& ejercicios, const QString& nivel)
{
    QList<Ejercicio> filtrados;
    
    for (const Ejercicio& ejercicio : ejercicios) {
        if (ejercicio.nivel == nivel || 
           (nivel == "intermedio" && ejercicio.nivel == "basico") ||
           (nivel == "avanzado" && (ejercicio.nivel == "basico" || ejercicio.nivel == "intermedio"))) {
            filtrados.append(ejercicio);
        }
    }
    
    return filtrados;
}

QList<Ejercicio> RutinaGenerator::filtrarPorGrupoMuscular(const QList<Ejercicio>& ejercicios, const QString& grupo)
{
    QList<Ejercicio> filtrados;
    
    for (const Ejercicio& ejercicio : ejercicios) {
        if (ejercicio.grupoMuscular == grupo) {
            filtrados.append(ejercicio);
        }
    }
    
    return filtrados;
}

QStringList RutinaGenerator::crearRutinaDia(const QList<Ejercicio>& ejercicios, int cantidad)
{
    QStringList rutina;
    
    if (ejercicios.isEmpty()) {
        rutina << "No hay ejercicios disponibles para este día";
        return rutina;
    }
    
    // Seleccionar ejercicios aleatoriamente sin repetir
    QList<int> indicesUsados;
    int maxEjercicios = qMin(cantidad, ejercicios.size());
    
    for (int i = 0; i < maxEjercicios; ++i) {
        int indice;
        do {
            indice = QRandomGenerator::global()->bounded(ejercicios.size());
        } while (indicesUsados.contains(indice));
        
        indicesUsados.append(indice);
        
        const Ejercicio& ejercicio = ejercicios[indice];
        QString descripcion = QString("%1 - %2 series x %3 repeticiones")
                             .arg(ejercicio.nombre)
                             .arg(ejercicio.series)
                             .arg(ejercicio.repeticiones);
        
        rutina.append(descripcion);
    }
    
    return rutina;
}

QStringList RutinaGenerator::getDiasPorObjetivo(const QString& objetivo)
{
    if (objetivo == "Ganar músculo") {
        return {"Lunes", "Martes", "Miércoles", "Viernes", "Sábado"};
    } else if (objetivo == "Perder peso") {
        return {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes"};
    } else if (objetivo == "Ganar peso") {
        return {"Lunes", "Miércoles", "Viernes", "Sábado"};
    } else { // Mantener estado físico
        return {"Lunes", "Miércoles", "Viernes"};
    }
}
