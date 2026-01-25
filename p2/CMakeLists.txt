cmake_minimum_required(VERSION 3.16)

project(p2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(p2 main.cpp
    problemas.h problemas.cpp)

include(GNUInstallDirs)
install(TARGETS p2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
