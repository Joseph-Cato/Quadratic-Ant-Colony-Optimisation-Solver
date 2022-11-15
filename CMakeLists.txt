cmake_minimum_required(VERSION 3.24)
project(Quadratic_Ant_Colony_Optimisation_Solver)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(Quadratic_Ant_Colony_Optimisation_Solver
        main.cpp Ant.cpp Ant.h Graph.cpp Graph.h)
