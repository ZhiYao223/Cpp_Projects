# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest/build

# Include any dependencies generated for this target.
include CMakeFiles/appstatic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/appstatic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/appstatic.dir/flags.make

CMakeFiles/appstatic.dir/main.cpp.o: CMakeFiles/appstatic.dir/flags.make
CMakeFiles/appstatic.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/appstatic.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/appstatic.dir/main.cpp.o -c /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest/main.cpp

CMakeFiles/appstatic.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/appstatic.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest/main.cpp > CMakeFiles/appstatic.dir/main.cpp.i

CMakeFiles/appstatic.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/appstatic.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest/main.cpp -o CMakeFiles/appstatic.dir/main.cpp.s

# Object files for target appstatic
appstatic_OBJECTS = \
"CMakeFiles/appstatic.dir/main.cpp.o"

# External object files for target appstatic
appstatic_EXTERNAL_OBJECTS =

../bin/appstatic: CMakeFiles/appstatic.dir/main.cpp.o
../bin/appstatic: CMakeFiles/appstatic.dir/build.make
../bin/appstatic: ../lib/libOurLib.so
../bin/appstatic: CMakeFiles/appstatic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/appstatic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/appstatic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/appstatic.dir/build: ../bin/appstatic

.PHONY : CMakeFiles/appstatic.dir/build

CMakeFiles/appstatic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/appstatic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/appstatic.dir/clean

CMakeFiles/appstatic.dir/depend:
	cd /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest/build /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest/build /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeLibTest/build/CMakeFiles/appstatic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/appstatic.dir/depend

