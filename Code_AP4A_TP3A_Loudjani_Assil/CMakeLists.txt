cmake_minimum_required(VERSION 3.16)

project(AP4A-Projet-TP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AP4A-Projet-TP main.cpp
    Logger.h
    Scheduler.h
    LecteurBadge.h
    Server.h
    Server.cpp
    LecteurBadge.cpp
    Logger.cpp
    Scheduler.cpp
    Badge.h
    Badge.cpp)

include(GNUInstallDirs)
install(TARGETS AP4A-Projet-TP
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
