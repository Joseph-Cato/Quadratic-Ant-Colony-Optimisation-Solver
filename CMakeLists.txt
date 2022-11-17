cmake_minimum_required(VERSION 3.24)
project(Quadratic_Ant_Colony_Optimisation_Solver)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

add_subdirectory(src)
add_subdirectory(lib/googletest)
add_subdirectory(test)



