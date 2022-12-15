set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(Quadratic_Ant_Colony_Optimisation_Solver
        main.cpp Ant.cpp Ant.h Graph.cpp Graph.h ../lib/CTPL/ctpl_stl.h ../lib/CTPL/ctpl.h)

set(SOURCES ${SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -lm -O2 -static-libstdc++ -static-libgcc -pthread -flto")

add_executable(${BINARY}_run main.cpp Ant.h Ant.cpp Graph.h Graph.cpp ../lib/CTPL/ctpl_stl.h ../lib/CTPL/ctpl.h)

add_library(${BINARY}_lib STATIC main.cpp Ant.h Ant.cpp Graph.h Graph.cpp ../lib/CTPL/ctpl_stl.h ../lib/CTPL/ctpl.h)