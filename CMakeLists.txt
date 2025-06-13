cmake_minimum_required(VERSION 3.16)
project(GymApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

# Habilitar automoc para Qt - ESTO ES CRUCIAL
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    main.cpp
    mainwindow.cpp
    loginwindow.cpp
    registerwindow.cpp
    rutinaswindow.cpp
    database.cpp
    rutinagenerator.cpp
)

set(HEADERS
    mainwindow.h
    loginwindow.h
    registerwindow.h
    rutinaswindow.h
    database.h
    rutinagenerator.h
)

add_executable(GymApp ${SOURCES} ${HEADERS})

target_link_libraries(GymApp Qt6::Core Qt6::Widgets Qt6::Sql)
