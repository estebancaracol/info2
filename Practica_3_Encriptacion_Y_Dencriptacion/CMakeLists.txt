cmake_minimum_required(VERSION 3.16)

project(Practica_3_Encriptacion_Y_Dencriptacion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Practica_3_Encriptacion_Y_Dencriptacion main.cpp
    metodos.h metodos.cpp
    cajero.h cajero.cpp
    procesamiento.h procesamiento.cpp
    auxiliares.h auxiliares.cpp
)

include(GNUInstallDirs)
install(TARGETS Practica_3_Encriptacion_Y_Dencriptacion
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
