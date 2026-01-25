cmake_minimum_required(VERSION 3.16)

project(Practica_4_Sistema_de_Simulacion_de_Red_de_Enrutadores LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Practica_4_Sistema_de_Simulacion_de_Red_de_Enrutadores main.cpp
    red.h red.cpp
    enrutador.h enrutador.cpp)

include(GNUInstallDirs)
install(TARGETS Practica_4_Sistema_de_Simulacion_de_Red_de_Enrutadores
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
