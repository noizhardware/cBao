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
include CMakeFiles/timer_static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/timer_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/timer_static.dir/flags.make

CMakeFiles/timer_static.dir/progs/demos/timer/timer.c.obj: CMakeFiles/timer_static.dir/flags.make
CMakeFiles/timer_static.dir/progs/demos/timer/timer.c.obj: CMakeFiles/timer_static.dir/includes_C.rsp
CMakeFiles/timer_static.dir/progs/demos/timer/timer.c.obj: progs/demos/timer/timer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=R:\scripts\C\include\freeglut-3.0.0\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/timer_static.dir/progs/demos/timer/timer.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\timer_static.dir\progs\demos\timer\timer.c.obj   -c R:\scripts\C\include\freeglut-3.0.0\progs\demos\timer\timer.c

CMakeFiles/timer_static.dir/progs/demos/timer/timer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timer_static.dir/progs/demos/timer/timer.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E R:\scripts\C\include\freeglut-3.0.0\progs\demos\timer\timer.c > CMakeFiles\timer_static.dir\progs\demos\timer\timer.c.i

CMakeFiles/timer_static.dir/progs/demos/timer/timer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timer_static.dir/progs/demos/timer/timer.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S R:\scripts\C\include\freeglut-3.0.0\progs\demos\timer\timer.c -o CMakeFiles\timer_static.dir\progs\demos\timer\timer.c.s

# Object files for target timer_static
timer_static_OBJECTS = \
"CMakeFiles/timer_static.dir/progs/demos/timer/timer.c.obj"

# External object files for target timer_static
timer_static_EXTERNAL_OBJECTS =

bin/timer_static.exe: CMakeFiles/timer_static.dir/progs/demos/timer/timer.c.obj
bin/timer_static.exe: CMakeFiles/timer_static.dir/build.make
bin/timer_static.exe: lib/libfreeglut_static.a
bin/timer_static.exe: CMakeFiles/timer_static.dir/linklibs.rsp
bin/timer_static.exe: CMakeFiles/timer_static.dir/objects1.rsp
bin/timer_static.exe: CMakeFiles/timer_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=R:\scripts\C\include\freeglut-3.0.0\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin\timer_static.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\timer_static.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/timer_static.dir/build: bin/timer_static.exe

.PHONY : CMakeFiles/timer_static.dir/build

CMakeFiles/timer_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\timer_static.dir\cmake_clean.cmake
.PHONY : CMakeFiles/timer_static.dir/clean

CMakeFiles/timer_static.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" R:\scripts\C\include\freeglut-3.0.0 R:\scripts\C\include\freeglut-3.0.0 R:\scripts\C\include\freeglut-3.0.0 R:\scripts\C\include\freeglut-3.0.0 R:\scripts\C\include\freeglut-3.0.0\CMakeFiles\timer_static.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/timer_static.dir/depend

