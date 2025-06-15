#include "rutinagenerator.h"
#include <QRandomGenerator>

QMap<QString, QStringList> RutinaGenerator::generarRutinaSemanal(const Usuario& usuario)
{
    QMap<QString, QStringList> rutinaSemanal;
    QList<Ejercicio> todosEjercicios = obtenerEjercicios();
    QList<Ejercicio> ejerciciosFiltrados = filtrarPorNivel(todosEjercicios, usuario.nivelGimnasio);
    
    QStringList diasActivos = getDiasPorObjetivo(usuario.objetivo);
    QStringList todosDias = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
    QStringList gruposMusculares = getGruposMuscularesPorObjetivo(usuario.objetivo);
    
    int diaIndex = 0;
    for (const QString& dia : todosDias) {
        if (diasActivos.contains(dia) && diaIndex < gruposMusculares.size()) {
            QString grupo = gruposMusculares[diaIndex];
            QList<Ejercicio> ejerciciosGrupo = filtrarPorGrupoMuscular(ejerciciosFiltrados, grupo);
            
            rutinaSemanal[dia] = crearRutinaDia(ejerciciosGrupo, usuario.objetivo, usuario.nivelGimnasio);
            diaIndex++;
        } else {
            QString mensajeDescanso = "Día de descanso - ¡Recupera tu energía!";
            if (usuario.tieneMascotas) {
                mensajeDescanso += "\n💡 Aprovecha para dar un paseo con tu mascota";
            }
            rutinaSemanal[dia] = QStringList() << mensajeDescanso;
        }
    }
    
    return rutinaSemanal;
}

QStringList RutinaGenerator::crearRutinaDia(const QList<Ejercicio>& ejercicios, const QString& objetivo, const QString& nivel)
{
    if (ejercicios.isEmpty()) {
        return QStringList() << "No hay ejercicios disponibles para este día";
    }
    
    // Determinar tipo de rutina basado en el objetivo
    if (objetivo == "Ganar músculo") {
        return crearRutinaHipertrofia(ejercicios, ejercicios.first().grupoMuscular, nivel);
    } else if (objetivo == "Perder peso") {
        return crearRutinaPerdidaGrasa(ejercicios, ejercicios.first().grupoMuscular, nivel);
    } else if (objetivo == "Ganar peso") {
        return crearRutinaFuerza(ejercicios, ejercicios.first().grupoMuscular, nivel);
    } else { // Mantener estado físico
        return crearRutinaResistencia(ejercicios, nivel);
    }
}

QStringList RutinaGenerator::crearRutinaHipertrofia(const QList<Ejercicio>& ejercicios, const QString& grupoMuscular, const QString& nivel)
{
    QStringList rutina;
    QList<Ejercicio> compuestos = filtrarPorTipo(ejercicios, "compuesto");
    QList<Ejercicio> accesorios = filtrarPorTipo(ejercicios, "accesorio");
    
    // 5-6 ejercicios: 2 compuestos + 3-4 accesorios
    int totalEjercicios = (nivel == "basico") ? 5 : 6;
    int ejerciciosCompuestos = 2;
    int ejerciciosAccesorios = totalEjercicios - ejerciciosCompuestos;
    
    rutina << QString("🎯 HIPERTROFIA - %1").arg(grupoMuscular);
    rutina << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    
    // Agregar ejercicios compuestos
    QList<int> indicesUsados;
    for (int i = 0; i < ejerciciosCompuestos && i < compuestos.size(); ++i) {
        int indice;
        do {
            indice = QRandomGenerator::global()->bounded(compuestos.size());
        } while (indicesUsados.contains(indice));
        
        indicesUsados.append(indice);
        const Ejercicio& ejercicio = compuestos[indice];
        rutina << QString("🏋️ %1 - %2 series x %3")
                     .arg(ejercicio.nombre)
                     .arg(ejercicio.series)
                     .arg(ejercicio.repeticiones);
        if (!ejercicio.descripcion.isEmpty()) {
            rutina << QString("   💡 %1").arg(ejercicio.descripcion);
        }
    }
    
    // Agregar ejercicios accesorios
    indicesUsados.clear();
    for (int i = 0; i < ejerciciosAccesorios && i < accesorios.size(); ++i) {
        int indice;
        do {
            indice = QRandomGenerator::global()->bounded(accesorios.size());
        } while (indicesUsados.contains(indice));
        
        indicesUsados.append(indice);
        const Ejercicio& ejercicio = accesorios[indice];
        rutina << QString("💪 %1 - %2 series x %3")
                     .arg(ejercicio.nombre)
                     .arg(ejercicio.series)
                     .arg(ejercicio.repeticiones);
        if (!ejercicio.descripcion.isEmpty()) {
            rutina << QString("   💡 %1").arg(ejercicio.descripcion);
        }
    }
    
    rutina << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    rutina << "⏱️ Descanso entre series: 60-90 segundos";
    
    return rutina;
}

QStringList RutinaGenerator::crearRutinaFuerza(const QList<Ejercicio>& ejercicios, const QString& grupoMuscular, const QString& nivel)
{
    QStringList rutina;
    QList<Ejercicio> compuestos = filtrarPorTipo(ejercicios, "compuesto");
    QList<Ejercicio> accesorios = filtrarPorTipo(ejercicios, "accesorio");
    
    // 3-5 ejercicios: 1-2 principales + 2-3 auxiliares
    int totalEjercicios = (nivel == "basico") ? 3 : 5;
    int ejerciciosPrincipales = (nivel == "basico") ? 1 : 2;
    int ejerciciosAuxiliares = totalEjercicios - ejerciciosPrincipales;
    
    rutina << QString("💥 FUERZA - %1").arg(grupoMuscular);
    rutina << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    
    // Agregar ejercicios principales (compuestos con menos reps, más peso)
    QList<int> indicesUsados;
    for (int i = 0; i < ejerciciosPrincipales && i < compuestos.size(); ++i) {
        int indice;
        do {
            indice = QRandomGenerator::global()->bounded(compuestos.size());
        } while (indicesUsados.contains(indice));
        
        indicesUsados.append(indice);
        const Ejercicio& ejercicio = compuestos[indice];
        // Para fuerza: menos reps, más series
        rutina << QString("🔥 %1 - %2 series x 3-5 reps (peso alto)")
                     .arg(ejercicio.nombre)
                     .arg(ejercicio.series + 1);
        if (!ejercicio.descripcion.isEmpty()) {
            rutina << QString("   💡 %1").arg(ejercicio.descripcion);
        }
    }
    
    // Agregar ejercicios auxiliares
    indicesUsados.clear();
    for (int i = 0; i < ejerciciosAuxiliares && i < accesorios.size(); ++i) {
        int indice;
        do {
            indice = QRandomGenerator::global()->bounded(accesorios.size());
        } while (indicesUsados.contains(indice));
        
        indicesUsados.append(indice);
        const Ejercicio& ejercicio = accesorios[indice];
        rutina << QString("💪 %1 - %2 series x %3")
                     .arg(ejercicio.nombre)
                     .arg(ejercicio.series)
                     .arg(ejercicio.repeticiones);
    }
    
    rutina << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    rutina << "⏱️ Descanso entre series: 2-3 minutos";
    
    return rutina;
}

QStringList RutinaGenerator::crearRutinaResistencia(const QList<Ejercicio>& ejercicios, const QString& nivel)
{
    QStringList rutina;
    
    // 4-6 ejercicios: 1 por grupo muscular principal
    int totalEjercicios = (nivel == "basico") ? 4 : 6;
    
    rutina << "🏃 RESISTENCIA MUSCULAR - Full Body";
    rutina << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    
    // Seleccionar ejercicios de diferentes grupos musculares
    QStringList gruposUsados;
    QList<int> indicesUsados;
    
    for (int i = 0; i < totalEjercicios && i < ejercicios.size(); ++i) {
        int indice;
        QString grupo;
        int intentos = 0;
        
        do {
            indice = QRandomGenerator::global()->bounded(ejercicios.size());
            grupo = ejercicios[indice].grupoMuscular;
            intentos++;
        } while ((indicesUsados.contains(indice) || gruposUsados.contains(grupo)) && intentos < 50);
        
        if (intentos < 50) {
            indicesUsados.append(indice);
            gruposUsados.append(grupo);
            
            const Ejercicio& ejercicio = ejercicios[indice];
            rutina << QString("🔄 %1 - %2 series x 12-20 reps")
                         .arg(ejercicio.nombre)
                         .arg(ejercicio.series);
        }
    }
    
    rutina << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    rutina << "⏱️ Descanso entre series: 30-45 segundos";
    rutina << "💡 Circuito: Haz todos los ejercicios seguidos";
    
    return rutina;
}

QStringList RutinaGenerator::crearRutinaPerdidaGrasa(const QList<Ejercicio>& ejercicios, const QString& grupoMuscular, const QString& nivel)
{
    QStringList rutina;
    QList<Ejercicio> pesas = ejercicios;
    QList<Ejercicio> cardio = filtrarPorGrupoMuscular(obtenerEjercicios(), "Cardio");
    cardio = filtrarPorNivel(cardio, nivel);
    
    // 4-5 ejercicios de pesas + cardio
    int ejerciciosPesas = (nivel == "basico") ? 4 : 5;
    
    rutina << QString("🔥 PÉRDIDA DE GRASA - %1 + Cardio").arg(grupoMuscular);
    rutina << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    
    // Ejercicios de pesas en formato de circuito/superseries
    QList<int> indicesUsados;
    for (int i = 0; i < ejerciciosPesas && i < pesas.size(); ++i) {
        int indice;
        do {
            indice = QRandomGenerator::global()->bounded(pesas.size());
        } while (indicesUsados.contains(indice));
        
        indicesUsados.append(indice);
        const Ejercicio& ejercicio = pesas[indice];
        rutina << QString("⚡ %1 - %2 series x %3")
                     .arg(ejercicio.nombre)
                     .arg(ejercicio.series)
                     .arg(ejercicio.repeticiones);
    }
    
    // Agregar cardio
    if (!cardio.isEmpty()) {
        int indiceCardio = QRandomGenerator::global()->bounded(cardio.size());
        const Ejercicio& ejercicioCardio = cardio[indiceCardio];
        rutina << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
        rutina << QString("🏃 %1 - %2")
                     .arg(ejercicioCardio.nombre)
                     .arg(ejercicioCardio.repeticiones);
    }
    
    rutina << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    rutina << "⏱️ Descanso entre ejercicios: 30-45 segundos";
    rutina << "💡 Formato superserie para mayor quema calórica";
    
    return rutina;
}

QList<Ejercicio> RutinaGenerator::obtenerEjercicios()
{
    QList<Ejercicio> ejercicios;
    
    // ================ EJERCICIOS DE PECHO ================
    ejercicios << Ejercicio{"Press de banca", "Pecho", "basico", "compuesto", 3, "8-12", "Ejercicio principal para desarrollo del pecho"};
    ejercicios << Ejercicio{"Flexiones", "Pecho", "basico", "compuesto", 3, "10-15", "Peso corporal, modifica la inclinación para variar dificultad"};
    ejercicios << Ejercicio{"Press inclinado con mancuernas", "Pecho", "intermedio", "compuesto", 4, "8-10", "Enfoque en pecho superior"};
    ejercicios << Ejercicio{"Aperturas con mancuernas", "Pecho", "intermedio", "accesorio", 3, "10-12", "Aislamiento del pecho, controla el movimiento"};
    ejercicios << Ejercicio{"Press declinado", "Pecho", "avanzado", "compuesto", 4, "6-8", "Enfoque en pecho inferior"};
    ejercicios << Ejercicio{"Dips en paralelas", "Pecho", "avanzado", "compuesto", 3, "8-12", "Inclínate hacia adelante para enfoque en pecho"};
    ejercicios << Ejercicio{"Aperturas en polea alta", "Pecho", "intermedio", "accesorio", 3, "12-15", "Mantén tensión constante"};
    ejercicios << Ejercicio{"Press con mancuernas plano", "Pecho", "basico", "compuesto", 3, "8-12", "Mayor rango de movimiento que barra"};
    ejercicios << Ejercicio{"Pullover con mancuerna", "Pecho", "intermedio", "accesorio", 3, "10-12", "También trabaja serratos"};
    ejercicios << Ejercicio{"Flexiones diamante", "Pecho", "avanzado", "compuesto", 3, "6-10", "Mayor activación de tríceps"};
    
    // ================ EJERCICIOS DE ESPALDA ================
    ejercicios << Ejercicio{"Dominadas asistidas", "Espalda", "basico", "compuesto", 3, "5-8", "Usa asistencia hasta dominar el movimiento"};
    ejercicios << Ejercicio{"Remo con mancuerna", "Espalda", "basico", "compuesto", 3, "8-12", "Apóyate en banco, mantén espalda recta"};
    ejercicios << Ejercicio{"Jalones al pecho", "Espalda", "intermedio", "compuesto", 4, "8-10", "Inclínate ligeramente hacia atrás"};
    ejercicios << Ejercicio{"Remo en polea baja", "Espalda", "intermedio", "compuesto", 3, "10-12", "Mantén pecho hacia afuera"};
    ejercicios << Ejercicio{"Dominadas", "Espalda", "avanzado", "compuesto", 4, "5-10", "Ejercicio rey para espalda"};
    ejercicios << Ejercicio{"Peso muerto", "Espalda", "avanzado", "compuesto", 4, "6-8", "Técnica crucial, empieza con poco peso"};
    ejercicios << Ejercicio{"Remo con barra", "Espalda", "intermedio", "compuesto", 4, "8-10", "Mantén core activado"};
    ejercicios << Ejercicio{"Jalones con agarre neutro", "Espalda", "basico", "compuesto", 3, "10-12", "Agarre más natural para los hombros"};
    ejercicios << Ejercicio{"Face pulls", "Espalda", "intermedio", "accesorio", 3, "12-15", "Excelente para deltoides posteriores"};
    ejercicios << Ejercicio{"Remo en T", "Espalda", "avanzado", "compuesto", 4, "8-10", "Posición estable para cargar más peso"};
    ejercicios << Ejercicio{"Hiperextensiones", "Espalda", "basico", "accesorio", 3, "10-15", "Fortalece zona lumbar"};
    ejercicios << Ejercicio{"Encogimientos con mancuernas", "Espalda", "basico", "accesorio", 3, "10-12", "Enfoque en trapecios superiores"};
    
    // ================ EJERCICIOS DE PIERNAS ================
    ejercicios << Ejercicio{"Sentadillas", "Piernas", "basico", "compuesto", 3, "12-15", "Rey de los ejercicios de piernas"};
    ejercicios << Ejercicio{"Prensa de piernas", "Piernas", "basico", "compuesto", 3, "10-12", "Alternativa segura a sentadillas"};
    ejercicios << Ejercicio{"Zancadas", "Piernas", "intermedio", "compuesto", 3, "10-12 c/u", "Trabaja cada pierna independientemente"};
    ejercicios << Ejercicio{"Extensiones de cuádriceps", "Piernas", "intermedio", "accesorio", 3, "12-15", "Aislamiento de cuádriceps"};
    ejercicios << Ejercicio{"Sentadilla búlgara", "Piernas", "avanzado", "compuesto", 4, "8-10 c/u", "Excelente para glúteos y cuádriceps"};
    ejercicios << Ejercicio{"Peso muerto rumano", "Piernas", "avanzado", "compuesto", 4, "8-10", "Enfoque en isquiotibiales y glúteos"};
    ejercicios << Ejercicio{"Curl de isquiotibiales", "Piernas", "basico", "accesorio", 3, "10-12", "Aislamiento de parte posterior del muslo"};
    ejercicios << Ejercicio{"Elevaciones de gemelos", "Piernas", "basico", "accesorio", 4, "15-20", "No olvides las pantorrillas"};
    ejercicios << Ejercicio{"Sentadilla goblet", "Piernas", "basico", "compuesto", 3, "10-12", "Buena para aprender técnica"};
    ejercicios << Ejercicio{"Step ups", "Piernas", "intermedio", "compuesto", 3, "10-12 c/u", "Funcional y unilateral"};
    ejercicios << Ejercicio{"Sentadilla sumo", "Piernas", "intermedio", "compuesto", 3, "10-12", "Mayor activación de aductores"};
    ejercicios << Ejercicio{"Hip thrust", "Piernas", "intermedio", "compuesto", 3, "10-12", "Excelente para glúteos"};
    
    // ================ EJERCICIOS DE BRAZOS ================
    ejercicios << Ejercicio{"Curl de bíceps", "Brazos", "basico", "accesorio", 3, "10-12", "Ejercicio básico para bíceps"};
    ejercicios << Ejercicio{"Extensiones de tríceps", "Brazos", "basico", "accesorio", 3, "10-12", "Aislamiento de tríceps"};
    ejercicios << Ejercicio{"Curl martillo", "Brazos", "intermedio", "accesorio", 3, "8-10", "Trabaja bíceps y antebrazo"};
    ejercicios << Ejercicio{"Dips en banco", "Brazos", "intermedio", "compuesto", 3, "8-12", "Compuesto para tríceps"};
    ejercicios << Ejercicio{"Curl con barra", "Brazos", "avanzado", "accesorio", 4, "6-8", "Permite cargar más peso"};
    ejercicios << Ejercicio{"Press francés", "Brazos", "avanzado", "accesorio", 4, "8-10", "Aislamiento intenso de tríceps"};
    ejercicios << Ejercicio{"Curl concentrado", "Brazos", "intermedio", "accesorio", 3, "8-10", "Aislamiento total del bíceps"};
    ejercicios << Ejercicio{"Extensiones en polea alta", "Brazos", "basico", "accesorio", 3, "10-12", "Movimiento constante de tríceps"};
    ejercicios << Ejercicio{"Curl 21s", "Brazos", "avanzado", "accesorio", 3, "21 reps", "7 parciales abajo + 7 arriba + 7 completas"};
    ejercicios << Ejercicio{"Patadas de tríceps", "Brazos", "intermedio", "accesorio", 3, "10-12", "Aislamiento unilateral"};
    
    // ================ EJERCICIOS DE HOMBROS ================
    ejercicios << Ejercicio{"Press militar con mancuernas", "Hombros", "basico", "compuesto", 3, "8-10", "Desarrollo integral de hombros"};
    ejercicios << Ejercicio{"Elevaciones laterales", "Hombros", "basico", "accesorio", 3, "10-12", "Aislamiento de deltoides medios"};
    ejercicios << Ejercicio{"Elevaciones frontales", "Hombros", "intermedio", "accesorio", 3, "10-12", "Enfoque en deltoides anteriores"};
    ejercicios << Ejercicio{"Remo al mentón", "Hombros", "intermedio", "compuesto", 3, "8-10", "Trabaja hombros y trapecios"};
    ejercicios << Ejercicio{"Press militar con barra", "Hombros", "avanzado", "compuesto", 4, "6-8", "Ejercicio clásico de fuerza"};
    ejercicios << Ejercicio{"Elevaciones posteriores", "Hombros", "avanzado", "accesorio", 3, "10-12", "Deltoides posteriores importantes"};
    ejercicios << Ejercicio{"Arnold press", "Hombros", "avanzado", "compuesto", 3, "8-10", "Rotación completa del hombro"};
    ejercicios << Ejercicio{"Elevaciones laterales en polea", "Hombros", "intermedio", "accesorio", 3, "12-15", "Tensión constante"};
    ejercicios << Ejercicio{"Press tras nuca", "Hombros", "avanzado", "compuesto", 3, "8-10", "Solo si tienes buena movilidad"};
    ejercicios << Ejercicio{"Cruces posteriores en polea", "Hombros", "intermedio", "accesorio", 3, "12-15", "Excelente para postura"};
    
    // ================ EJERCICIOS DE CARDIO ================
    ejercicios << Ejercicio{"Caminata rápida", "Cardio", "basico", "cardio", 1, "20-30 min", "Bajo impacto, ideal para principiantes"};
    ejercicios << Ejercicio{"Bicicleta estática", "Cardio", "basico", "cardio", 1, "15-25 min", "Bueno para las rodillas"};
    ejercicios << Ejercicio{"Elíptica", "Cardio", "intermedio", "cardio", 1, "20-30 min", "Movimiento completo del cuerpo"};
    ejercicios << Ejercicio{"Intervalos en cinta", "Cardio", "intermedio", "cardio", 1, "15-20 min", "1 min rápido, 2 min lento"};
    ejercicios << Ejercicio{"Burpees", "Cardio", "avanzado", "cardio", 3, "10-15", "Ejercicio completo de alta intensidad"};
    ejercicios << Ejercicio{"Mountain climbers", "Cardio", "avanzado", "cardio", 3, "30-45 seg", "Cardio + core"};
    ejercicios << Ejercicio{"Jumping jacks", "Cardio", "basico", "cardio", 3, "20-30", "Activación cardiovascular rápida"};
    ejercicios << Ejercicio{"Escaladora", "Cardio", "intermedio", "cardio", 1, "15-25 min", "Bajo impacto, alta intensidad"};
    ejercicios << Ejercicio{"Remo en máquina", "Cardio", "intermedio", "cardio", 1, "15-20 min", "Trabajas todo el cuerpo"};
    ejercicios << Ejercicio{"Sprint en bicicleta", "Cardio", "avanzado", "cardio", 5, "30 seg", "Intervalos de alta intensidad"};
    
    // ================ EJERCICIOS DE CORE ================
    ejercicios << Ejercicio{"Plancha", "Core", "basico", "accesorio", 3, "30-60 seg", "Ejercicio base para el core"};
    ejercicios << Ejercicio{"Crunches", "Core", "basico", "accesorio", 3, "15-20", "Básico para abdominales superiores"};
    ejercicios << Ejercicio{"Plancha lateral", "Core", "intermedio", "accesorio", 3, "20-45 seg c/u", "Trabaja oblicuos"};
    ejercicios << Ejercicio{"Russian twists", "Core", "intermedio", "accesorio", 3, "20-30", "Rotación del tronco con peso"};
    ejercicios << Ejercicio{"Dead bug", "Core", "basico", "accesorio", 3, "10-12 c/u", "Estabilización del core"};
    ejercicios << Ejercicio{"Mountain climbers", "Core", "avanzado", "accesorio", 3, "20-30", "Cardio + fortalecimiento"};
    ejercicios << Ejercicio{"Bicycle crunches", "Core", "intermedio", "accesorio", 3, "20-30", "Trabajo cruzado de oblicuos"};
    ejercicios << Ejercicio{"Hanging leg raises", "Core", "avanzado", "accesorio", 3, "8-12", "Requiere fuerza de agarre"};
    ejercicios << Ejercicio{"Wood choppers", "Core", "intermedio", "accesorio", 3, "10-12 c/u", "Movimiento funcional con polea"};
    ejercicios << Ejercicio{"L-sits", "Core", "avanzado", "accesorio", 3, "10-20 seg", "Fuerza isométrica avanzada"};
    
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

QList<Ejercicio> RutinaGenerator::filtrarPorTipo(const QList<Ejercicio>& ejercicios, const QString& tipo)
{
    QList<Ejercicio> filtrados;
    
    for (const Ejercicio& ejercicio : ejercicios) {
        if (ejercicio.tipo == tipo) {
            filtrados.append(ejercicio);
        }
    }
    
    return filtrados;
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

QStringList RutinaGenerator::getGruposMuscularesPorObjetivo(const QString& objetivo)
{
    if (objetivo == "Ganar músculo") {
        return {"Pecho", "Espalda", "Piernas", "Brazos", "Hombros"};
    } else if (objetivo == "Perder peso") {
        return {"Cardio", "Pecho", "Piernas", "Espalda", "Brazos"};
    } else if (objetivo == "Ganar peso") {
        return {"Pecho", "Piernas", "Espalda", "Brazos"};
    } else { // Mantener estado físico
        return {"Pecho", "Piernas", "Espalda"};
    }
}
