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
CMAKE_COMMAND = /opt/clion-2018.3.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.3.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Submarine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Submarine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Submarine.dir/flags.make

CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.o: CMakeFiles/Submarine.dir/flags.make
CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.o: ../Programmatistikes/ask3/submarine/submarine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.o -c "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua/Programmatistikes/ask3/submarine/submarine.cpp"

CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua/Programmatistikes/ask3/submarine/submarine.cpp" > CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.i

CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua/Programmatistikes/ask3/submarine/submarine.cpp" -o CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.s

# Object files for target Submarine
Submarine_OBJECTS = \
"CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.o"

# External object files for target Submarine
Submarine_EXTERNAL_OBJECTS =

Submarine: CMakeFiles/Submarine.dir/Programmatistikes/ask3/submarine/submarine.cpp.o
Submarine: CMakeFiles/Submarine.dir/build.make
Submarine: CMakeFiles/Submarine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Submarine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Submarine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Submarine.dir/build: Submarine

.PHONY : CMakeFiles/Submarine.dir/build

CMakeFiles/Submarine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Submarine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Submarine.dir/clean

CMakeFiles/Submarine.dir/depend:
	cd "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua" "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua" "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua/cmake-build-debug" "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua/cmake-build-debug" "/media/guru/Storage/Documents/ECE/Soft Flow/Algorithms/2018-2019/Git/Algorithms-Ntua/cmake-build-debug/CMakeFiles/Submarine.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Submarine.dir/depend

