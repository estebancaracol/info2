cmake_minimum_required(VERSION 3.16)

project(P2pares LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(P2pares main.cpp
    problemas.h problemas.cpp
)

include(GNUInstallDirs)
install(TARGETS P2pares
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
