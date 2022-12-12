set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(Quadratic_Ant_Colony_Optimisation_Solver
        main.cpp Ant.cpp Ant.h Graph.cpp Graph.h)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run main.cpp Ant.h Ant.cpp Graph.h Graph.cpp ../lib/CTPL/ctpl_stl.h ../lib/CTPL/ctpl.h)

add_library(${BINARY}_lib STATIC main.cpp Ant.h Ant.cpp Graph.h Graph.cpp ../lib/CTPL/ctpl_stl.h ../lib/CTPL/ctpl.h)