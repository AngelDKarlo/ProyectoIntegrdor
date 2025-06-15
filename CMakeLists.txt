cmake_minimum_required(VERSION 3.16)
project(GymApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

# Habilitar automoc para Qt - CRUCIAL para el sistema de señales
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Fuentes del proyecto
set(SOURCES
    main.cpp
    mainwindow.cpp
    loginwindow.cpp
    registerwindow.cpp
    rutinaswindow.cpp
    database.cpp
    rutinagenerator.cpp
)

# Headers del proyecto  
set(HEADERS
    mainwindow.h
    loginwindow.h
    registerwindow.h
    rutinaswindow.h
    database.h
    rutinagenerator.h
)

# Crear ejecutable
add_executable(GymApp ${SOURCES} ${HEADERS})

# Enlazar librerías Qt
target_link_libraries(GymApp 
    Qt6::Core 
    Qt6::Widgets 
    Qt6::Sql
)

# Configuración adicional para Debug/Release
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(GymApp PRIVATE DEBUG_MODE)
endif()

# Copiar base de datos si existe
if(EXISTS "${CMAKE_SOURCE_DIR}/gym_app.db")
    configure_file("${CMAKE_SOURCE_DIR}/gym_app.db" 
                   "${CMAKE_BINARY_DIR}/gym_app.db" COPYONLY)
endif()

