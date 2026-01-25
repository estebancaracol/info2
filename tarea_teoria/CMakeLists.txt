cmake_minimum_required(VERSION 3.16)

project(tarea_teoria LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tarea_teoria main.cpp)

include(GNUInstallDirs)
install(TARGETS tarea_teoria
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
