cmake_minimum_required(VERSION 3.23)
project(LABYRINTHE C)

set(CMAKE_C_STANDARD 99)

add_executable(LABYRINTHE main.c plateau.c plateau.h pion.h pion.c tests.c tests.h cartestresors.c cartestresors.h Deroulement.c Deroulement.h affichage.c affichage.h)
