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
CMAKE_SOURCE_DIR = /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/build

# Include any dependencies generated for this target.
include CMakeFiles/staticlib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/staticlib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/staticlib.dir/flags.make

CMakeFiles/staticlib.dir/src/add.cpp.o: CMakeFiles/staticlib.dir/flags.make
CMakeFiles/staticlib.dir/src/add.cpp.o: ../src/add.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/staticlib.dir/src/add.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/staticlib.dir/src/add.cpp.o -c /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/add.cpp

CMakeFiles/staticlib.dir/src/add.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/staticlib.dir/src/add.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/add.cpp > CMakeFiles/staticlib.dir/src/add.cpp.i

CMakeFiles/staticlib.dir/src/add.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/staticlib.dir/src/add.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/add.cpp -o CMakeFiles/staticlib.dir/src/add.cpp.s

CMakeFiles/staticlib.dir/src/div.cpp.o: CMakeFiles/staticlib.dir/flags.make
CMakeFiles/staticlib.dir/src/div.cpp.o: ../src/div.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/staticlib.dir/src/div.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/staticlib.dir/src/div.cpp.o -c /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/div.cpp

CMakeFiles/staticlib.dir/src/div.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/staticlib.dir/src/div.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/div.cpp > CMakeFiles/staticlib.dir/src/div.cpp.i

CMakeFiles/staticlib.dir/src/div.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/staticlib.dir/src/div.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/div.cpp -o CMakeFiles/staticlib.dir/src/div.cpp.s

CMakeFiles/staticlib.dir/src/mult.cpp.o: CMakeFiles/staticlib.dir/flags.make
CMakeFiles/staticlib.dir/src/mult.cpp.o: ../src/mult.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/staticlib.dir/src/mult.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/staticlib.dir/src/mult.cpp.o -c /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/mult.cpp

CMakeFiles/staticlib.dir/src/mult.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/staticlib.dir/src/mult.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/mult.cpp > CMakeFiles/staticlib.dir/src/mult.cpp.i

CMakeFiles/staticlib.dir/src/mult.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/staticlib.dir/src/mult.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/mult.cpp -o CMakeFiles/staticlib.dir/src/mult.cpp.s

CMakeFiles/staticlib.dir/src/sub.cpp.o: CMakeFiles/staticlib.dir/flags.make
CMakeFiles/staticlib.dir/src/sub.cpp.o: ../src/sub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/staticlib.dir/src/sub.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/staticlib.dir/src/sub.cpp.o -c /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/sub.cpp

CMakeFiles/staticlib.dir/src/sub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/staticlib.dir/src/sub.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/sub.cpp > CMakeFiles/staticlib.dir/src/sub.cpp.i

CMakeFiles/staticlib.dir/src/sub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/staticlib.dir/src/sub.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/src/sub.cpp -o CMakeFiles/staticlib.dir/src/sub.cpp.s

# Object files for target staticlib
staticlib_OBJECTS = \
"CMakeFiles/staticlib.dir/src/add.cpp.o" \
"CMakeFiles/staticlib.dir/src/div.cpp.o" \
"CMakeFiles/staticlib.dir/src/mult.cpp.o" \
"CMakeFiles/staticlib.dir/src/sub.cpp.o"

# External object files for target staticlib
staticlib_EXTERNAL_OBJECTS =

../lib/libstaticlib.a: CMakeFiles/staticlib.dir/src/add.cpp.o
../lib/libstaticlib.a: CMakeFiles/staticlib.dir/src/div.cpp.o
../lib/libstaticlib.a: CMakeFiles/staticlib.dir/src/mult.cpp.o
../lib/libstaticlib.a: CMakeFiles/staticlib.dir/src/sub.cpp.o
../lib/libstaticlib.a: CMakeFiles/staticlib.dir/build.make
../lib/libstaticlib.a: CMakeFiles/staticlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library ../lib/libstaticlib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/staticlib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/staticlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/staticlib.dir/build: ../lib/libstaticlib.a

.PHONY : CMakeFiles/staticlib.dir/build

CMakeFiles/staticlib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/staticlib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/staticlib.dir/clean

CMakeFiles/staticlib.dir/depend:
	cd /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/build /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/build /home/zhiyao/Learnfiles/Cppfiles/Cpp_Projects/rectorproj/cmakeStaticLib/build/CMakeFiles/staticlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/staticlib.dir/depend

