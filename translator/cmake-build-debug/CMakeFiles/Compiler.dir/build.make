# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /opt/clion-2019.3.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.3.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aleksey/programming/Ded/my_lang/translator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aleksey/programming/Ded/my_lang/translator/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Compiler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Compiler.dir/flags.make

CMakeFiles/Compiler.dir/main.cpp.o: CMakeFiles/Compiler.dir/flags.make
CMakeFiles/Compiler.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aleksey/programming/Ded/my_lang/translator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Compiler.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Compiler.dir/main.cpp.o -c /home/aleksey/programming/Ded/my_lang/translator/main.cpp

CMakeFiles/Compiler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Compiler.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aleksey/programming/Ded/my_lang/translator/main.cpp > CMakeFiles/Compiler.dir/main.cpp.i

CMakeFiles/Compiler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Compiler.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aleksey/programming/Ded/my_lang/translator/main.cpp -o CMakeFiles/Compiler.dir/main.cpp.s

# Object files for target Compiler
Compiler_OBJECTS = \
"CMakeFiles/Compiler.dir/main.cpp.o"

# External object files for target Compiler
Compiler_EXTERNAL_OBJECTS =

Compiler: CMakeFiles/Compiler.dir/main.cpp.o
Compiler: CMakeFiles/Compiler.dir/build.make
Compiler: CMakeFiles/Compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aleksey/programming/Ded/my_lang/translator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Compiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Compiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Compiler.dir/build: Compiler

.PHONY : CMakeFiles/Compiler.dir/build

CMakeFiles/Compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Compiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Compiler.dir/clean

CMakeFiles/Compiler.dir/depend:
	cd /home/aleksey/programming/Ded/my_lang/translator/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aleksey/programming/Ded/my_lang/translator /home/aleksey/programming/Ded/my_lang/translator /home/aleksey/programming/Ded/my_lang/translator/cmake-build-debug /home/aleksey/programming/Ded/my_lang/translator/cmake-build-debug /home/aleksey/programming/Ded/my_lang/translator/cmake-build-debug/CMakeFiles/Compiler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Compiler.dir/depend

