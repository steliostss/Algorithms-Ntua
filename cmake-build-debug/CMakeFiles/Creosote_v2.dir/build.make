# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/56/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/56/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/guru/CLionProjects/Algorithms-Ntua

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/guru/CLionProjects/Algorithms-Ntua/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Creosote_v2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Creosote_v2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Creosote_v2.dir/flags.make

CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.o: CMakeFiles/Creosote_v2.dir/flags.make
CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.o: ../Programmatistikes/ask2/Creosote/creosote_v2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guru/CLionProjects/Algorithms-Ntua/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.o -c /home/guru/CLionProjects/Algorithms-Ntua/Programmatistikes/ask2/Creosote/creosote_v2.cpp

CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/guru/CLionProjects/Algorithms-Ntua/Programmatistikes/ask2/Creosote/creosote_v2.cpp > CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.i

CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/guru/CLionProjects/Algorithms-Ntua/Programmatistikes/ask2/Creosote/creosote_v2.cpp -o CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.s

# Object files for target Creosote_v2
Creosote_v2_OBJECTS = \
"CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.o"

# External object files for target Creosote_v2
Creosote_v2_EXTERNAL_OBJECTS =

Creosote_v2: CMakeFiles/Creosote_v2.dir/Programmatistikes/ask2/Creosote/creosote_v2.cpp.o
Creosote_v2: CMakeFiles/Creosote_v2.dir/build.make
Creosote_v2: CMakeFiles/Creosote_v2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/guru/CLionProjects/Algorithms-Ntua/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Creosote_v2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Creosote_v2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Creosote_v2.dir/build: Creosote_v2

.PHONY : CMakeFiles/Creosote_v2.dir/build

CMakeFiles/Creosote_v2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Creosote_v2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Creosote_v2.dir/clean

CMakeFiles/Creosote_v2.dir/depend:
	cd /home/guru/CLionProjects/Algorithms-Ntua/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/guru/CLionProjects/Algorithms-Ntua /home/guru/CLionProjects/Algorithms-Ntua /home/guru/CLionProjects/Algorithms-Ntua/cmake-build-debug /home/guru/CLionProjects/Algorithms-Ntua/cmake-build-debug /home/guru/CLionProjects/Algorithms-Ntua/cmake-build-debug/CMakeFiles/Creosote_v2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Creosote_v2.dir/depend

