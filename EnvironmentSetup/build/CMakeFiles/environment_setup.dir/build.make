# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /src/build

# Include any dependencies generated for this target.
include CMakeFiles/environment_setup.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/environment_setup.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/environment_setup.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/environment_setup.dir/flags.make

CMakeFiles/environment_setup.dir/main.cpp.o: CMakeFiles/environment_setup.dir/flags.make
CMakeFiles/environment_setup.dir/main.cpp.o: ../main.cpp
CMakeFiles/environment_setup.dir/main.cpp.o: CMakeFiles/environment_setup.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/environment_setup.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/environment_setup.dir/main.cpp.o -MF CMakeFiles/environment_setup.dir/main.cpp.o.d -o CMakeFiles/environment_setup.dir/main.cpp.o -c /src/main.cpp

CMakeFiles/environment_setup.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/environment_setup.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /src/main.cpp > CMakeFiles/environment_setup.dir/main.cpp.i

CMakeFiles/environment_setup.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/environment_setup.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /src/main.cpp -o CMakeFiles/environment_setup.dir/main.cpp.s

# Object files for target environment_setup
environment_setup_OBJECTS = \
"CMakeFiles/environment_setup.dir/main.cpp.o"

# External object files for target environment_setup
environment_setup_EXTERNAL_OBJECTS =

environment_setup: CMakeFiles/environment_setup.dir/main.cpp.o
environment_setup: CMakeFiles/environment_setup.dir/build.make
environment_setup: /usr/local/lib/libboost_filesystem.a
environment_setup: CMakeFiles/environment_setup.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable environment_setup"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/environment_setup.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/environment_setup.dir/build: environment_setup
.PHONY : CMakeFiles/environment_setup.dir/build

CMakeFiles/environment_setup.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/environment_setup.dir/cmake_clean.cmake
.PHONY : CMakeFiles/environment_setup.dir/clean

CMakeFiles/environment_setup.dir/depend:
	cd /src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /src /src /src/build /src/build /src/build/CMakeFiles/environment_setup.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/environment_setup.dir/depend

