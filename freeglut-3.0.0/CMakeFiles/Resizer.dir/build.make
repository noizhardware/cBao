# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = R:\scripts\C\include\freeglut-3.0.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = R:\scripts\C\include\freeglut-3.0.0

# Include any dependencies generated for this target.
include CMakeFiles/Resizer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Resizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Resizer.dir/flags.make

CMakeFiles/Resizer.dir/progs/demos/Resizer/Resizer.cpp.obj: CMakeFiles/Resizer.dir/flags.make
CMakeFiles/Resizer.dir/progs/demos/Resizer/Resizer.cpp.obj: CMakeFiles/Resizer.dir/includes_CXX.rsp
CMakeFiles/Resizer.dir/progs/demos/Resizer/Resizer.cpp.obj: progs/demos/Resizer/Resizer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=R:\scripts\C\include\freeglut-3.0.0\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Resizer.dir/progs/demos/Resizer/Resizer.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Resizer.dir\progs\demos\Resizer\Resizer.cpp.obj -c R:\scripts\C\include\freeglut-3.0.0\progs\demos\Resizer\Resizer.cpp

CMakeFiles/Resizer.dir/progs/demos/Resizer/Resizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Resizer.dir/progs/demos/Resizer/Resizer.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E R:\scripts\C\include\freeglut-3.0.0\progs\demos\Resizer\Resizer.cpp > CMakeFiles\Resizer.dir\progs\demos\Resizer\Resizer.cpp.i

CMakeFiles/Resizer.dir/progs/demos/Resizer/Resizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Resizer.dir/progs/demos/Resizer/Resizer.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S R:\scripts\C\include\freeglut-3.0.0\progs\demos\Resizer\Resizer.cpp -o CMakeFiles\Resizer.dir\progs\demos\Resizer\Resizer.cpp.s

# Object files for target Resizer
Resizer_OBJECTS = \
"CMakeFiles/Resizer.dir/progs/demos/Resizer/Resizer.cpp.obj"

# External object files for target Resizer
Resizer_EXTERNAL_OBJECTS =

bin/Resizer.exe: CMakeFiles/Resizer.dir/progs/demos/Resizer/Resizer.cpp.obj
bin/Resizer.exe: CMakeFiles/Resizer.dir/build.make
bin/Resizer.exe: lib/libfreeglut.dll.a
bin/Resizer.exe: CMakeFiles/Resizer.dir/linklibs.rsp
bin/Resizer.exe: CMakeFiles/Resizer.dir/objects1.rsp
bin/Resizer.exe: CMakeFiles/Resizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=R:\scripts\C\include\freeglut-3.0.0\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin\Resizer.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Resizer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Resizer.dir/build: bin/Resizer.exe

.PHONY : CMakeFiles/Resizer.dir/build

CMakeFiles/Resizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Resizer.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Resizer.dir/clean

CMakeFiles/Resizer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" R:\scripts\C\include\freeglut-3.0.0 R:\scripts\C\include\freeglut-3.0.0 R:\scripts\C\include\freeglut-3.0.0 R:\scripts\C\include\freeglut-3.0.0 R:\scripts\C\include\freeglut-3.0.0\CMakeFiles\Resizer.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Resizer.dir/depend

