cmake_minimum_required(VERSION 3.24)
project(Quadratic_Ant_Colony_Optimisation_Solver)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -lm -O2 -lstdc++ -flto")

#Add the google test subdirectory
add_subdirectory(./lib/googletest)

#include googletest/include dir
include_directories(./lib/googletest/googletest/include)

#include the googlemock/include dir
include_directories(./lib/googletest/googlemock/include)




add_subdirectory(src)
add_subdirectory(test)