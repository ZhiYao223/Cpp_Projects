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
CMAKE_SOURCE_DIR = /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake/build

# Include any dependencies generated for this target.
include CMakeFiles/servertest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/servertest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/servertest.dir/flags.make

CMakeFiles/servertest.dir/servertest.cpp.o: CMakeFiles/servertest.dir/flags.make
CMakeFiles/servertest.dir/servertest.cpp.o: ../servertest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/servertest.dir/servertest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servertest.dir/servertest.cpp.o -c /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake/servertest.cpp

CMakeFiles/servertest.dir/servertest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servertest.dir/servertest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake/servertest.cpp > CMakeFiles/servertest.dir/servertest.cpp.i

CMakeFiles/servertest.dir/servertest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servertest.dir/servertest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake/servertest.cpp -o CMakeFiles/servertest.dir/servertest.cpp.s

# Object files for target servertest
servertest_OBJECTS = \
"CMakeFiles/servertest.dir/servertest.cpp.o"

# External object files for target servertest
servertest_EXTERNAL_OBJECTS =

servertest: CMakeFiles/servertest.dir/servertest.cpp.o
servertest: CMakeFiles/servertest.dir/build.make
servertest: CMakeFiles/servertest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable servertest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/servertest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/servertest.dir/build: servertest

.PHONY : CMakeFiles/servertest.dir/build

CMakeFiles/servertest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/servertest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/servertest.dir/clean

CMakeFiles/servertest.dir/depend:
	cd /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake/build /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake/build /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/chapter5/5.2第一个网络通讯程序/TestWithCmake/build/CMakeFiles/servertest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/servertest.dir/depend

