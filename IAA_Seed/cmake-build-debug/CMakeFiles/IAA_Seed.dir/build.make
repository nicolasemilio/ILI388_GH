# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nicolasrojasmorales/CLionProjects/IAA_Seed

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/IAA_Seed.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IAA_Seed.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IAA_Seed.dir/flags.make

CMakeFiles/IAA_Seed.dir/main.cpp.o: CMakeFiles/IAA_Seed.dir/flags.make
CMakeFiles/IAA_Seed.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nicolasrojasmorales/CLionProjects/IAA_Seed/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IAA_Seed.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IAA_Seed.dir/main.cpp.o -c /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/main.cpp

CMakeFiles/IAA_Seed.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IAA_Seed.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/main.cpp > CMakeFiles/IAA_Seed.dir/main.cpp.i

CMakeFiles/IAA_Seed.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IAA_Seed.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/main.cpp -o CMakeFiles/IAA_Seed.dir/main.cpp.s

CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.o: CMakeFiles/IAA_Seed.dir/flags.make
CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.o: ../IOProcedures.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nicolasrojasmorales/CLionProjects/IAA_Seed/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.o -c /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/IOProcedures.cpp

CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/IOProcedures.cpp > CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.i

CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/IOProcedures.cpp -o CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.s

# Object files for target IAA_Seed
IAA_Seed_OBJECTS = \
"CMakeFiles/IAA_Seed.dir/main.cpp.o" \
"CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.o"

# External object files for target IAA_Seed
IAA_Seed_EXTERNAL_OBJECTS =

IAA_Seed: CMakeFiles/IAA_Seed.dir/main.cpp.o
IAA_Seed: CMakeFiles/IAA_Seed.dir/IOProcedures.cpp.o
IAA_Seed: CMakeFiles/IAA_Seed.dir/build.make
IAA_Seed: CMakeFiles/IAA_Seed.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nicolasrojasmorales/CLionProjects/IAA_Seed/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable IAA_Seed"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IAA_Seed.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IAA_Seed.dir/build: IAA_Seed

.PHONY : CMakeFiles/IAA_Seed.dir/build

CMakeFiles/IAA_Seed.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IAA_Seed.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IAA_Seed.dir/clean

CMakeFiles/IAA_Seed.dir/depend:
	cd /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nicolasrojasmorales/CLionProjects/IAA_Seed /Users/nicolasrojasmorales/CLionProjects/IAA_Seed /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/cmake-build-debug /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/cmake-build-debug /Users/nicolasrojasmorales/CLionProjects/IAA_Seed/cmake-build-debug/CMakeFiles/IAA_Seed.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IAA_Seed.dir/depend

