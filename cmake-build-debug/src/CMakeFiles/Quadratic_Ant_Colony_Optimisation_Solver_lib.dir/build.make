# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joseph/Documents/QACO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joseph/Documents/QACO/cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/flags.make

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.o: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/flags.make
src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.o: /home/joseph/Documents/QACO/src/main.cpp
src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.o: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joseph/Documents/QACO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.o"
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && /usr/bin/gcc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.o -MF CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.o.d -o CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.o -c /home/joseph/Documents/QACO/src/main.cpp

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.i"
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && /usr/bin/gcc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joseph/Documents/QACO/src/main.cpp > CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.i

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.s"
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && /usr/bin/gcc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joseph/Documents/QACO/src/main.cpp -o CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.s

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.o: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/flags.make
src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.o: /home/joseph/Documents/QACO/src/Ant.cpp
src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.o: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joseph/Documents/QACO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.o"
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && /usr/bin/gcc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.o -MF CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.o.d -o CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.o -c /home/joseph/Documents/QACO/src/Ant.cpp

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.i"
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && /usr/bin/gcc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joseph/Documents/QACO/src/Ant.cpp > CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.i

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.s"
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && /usr/bin/gcc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joseph/Documents/QACO/src/Ant.cpp -o CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.s

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.o: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/flags.make
src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.o: /home/joseph/Documents/QACO/src/Graph.cpp
src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.o: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joseph/Documents/QACO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.o"
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && /usr/bin/gcc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.o -MF CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.o.d -o CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.o -c /home/joseph/Documents/QACO/src/Graph.cpp

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.i"
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && /usr/bin/gcc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joseph/Documents/QACO/src/Graph.cpp > CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.i

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.s"
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && /usr/bin/gcc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joseph/Documents/QACO/src/Graph.cpp -o CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.s

# Object files for target Quadratic_Ant_Colony_Optimisation_Solver_lib
Quadratic_Ant_Colony_Optimisation_Solver_lib_OBJECTS = \
"CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.o" \
"CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.o" \
"CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.o"

# External object files for target Quadratic_Ant_Colony_Optimisation_Solver_lib
Quadratic_Ant_Colony_Optimisation_Solver_lib_EXTERNAL_OBJECTS =

src/libQuadratic_Ant_Colony_Optimisation_Solver_lib.a: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/main.cpp.o
src/libQuadratic_Ant_Colony_Optimisation_Solver_lib.a: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Ant.cpp.o
src/libQuadratic_Ant_Colony_Optimisation_Solver_lib.a: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/Graph.cpp.o
src/libQuadratic_Ant_Colony_Optimisation_Solver_lib.a: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/build.make
src/libQuadratic_Ant_Colony_Optimisation_Solver_lib.a: src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joseph/Documents/QACO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libQuadratic_Ant_Colony_Optimisation_Solver_lib.a"
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/cmake_clean_target.cmake
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/build: src/libQuadratic_Ant_Colony_Optimisation_Solver_lib.a
.PHONY : src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/build

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/clean:
	cd /home/joseph/Documents/QACO/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/clean

src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/depend:
	cd /home/joseph/Documents/QACO/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joseph/Documents/QACO /home/joseph/Documents/QACO/src /home/joseph/Documents/QACO/cmake-build-debug /home/joseph/Documents/QACO/cmake-build-debug/src /home/joseph/Documents/QACO/cmake-build-debug/src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/Quadratic_Ant_Colony_Optimisation_Solver_lib.dir/depend

