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
CMAKE_COMMAND = /home/anastasiia/Documents/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/anastasiia/Documents/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anastasiia/StringLibrary

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anastasiia/StringLibrary/cmake-build-debug

# Include any dependencies generated for this target.
include my_str/CMakeFiles/lib_string-shared.dir/depend.make

# Include the progress variables for this target.
include my_str/CMakeFiles/lib_string-shared.dir/progress.make

# Include the compile flags for this target's objects.
include my_str/CMakeFiles/lib_string-shared.dir/flags.make

my_str/CMakeFiles/lib_string-shared.dir/lib_string.c.o: my_str/CMakeFiles/lib_string-shared.dir/flags.make
my_str/CMakeFiles/lib_string-shared.dir/lib_string.c.o: ../my_str/lib_string.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anastasiia/StringLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object my_str/CMakeFiles/lib_string-shared.dir/lib_string.c.o"
	cd /home/anastasiia/StringLibrary/cmake-build-debug/my_str && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lib_string-shared.dir/lib_string.c.o   -c /home/anastasiia/StringLibrary/my_str/lib_string.c

my_str/CMakeFiles/lib_string-shared.dir/lib_string.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib_string-shared.dir/lib_string.c.i"
	cd /home/anastasiia/StringLibrary/cmake-build-debug/my_str && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anastasiia/StringLibrary/my_str/lib_string.c > CMakeFiles/lib_string-shared.dir/lib_string.c.i

my_str/CMakeFiles/lib_string-shared.dir/lib_string.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib_string-shared.dir/lib_string.c.s"
	cd /home/anastasiia/StringLibrary/cmake-build-debug/my_str && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anastasiia/StringLibrary/my_str/lib_string.c -o CMakeFiles/lib_string-shared.dir/lib_string.c.s

# Object files for target lib_string-shared
lib_string__shared_OBJECTS = \
"CMakeFiles/lib_string-shared.dir/lib_string.c.o"

# External object files for target lib_string-shared
lib_string__shared_EXTERNAL_OBJECTS =

my_str/liblib_string.so: my_str/CMakeFiles/lib_string-shared.dir/lib_string.c.o
my_str/liblib_string.so: my_str/CMakeFiles/lib_string-shared.dir/build.make
my_str/liblib_string.so: my_str/CMakeFiles/lib_string-shared.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anastasiia/StringLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library liblib_string.so"
	cd /home/anastasiia/StringLibrary/cmake-build-debug/my_str && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib_string-shared.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
my_str/CMakeFiles/lib_string-shared.dir/build: my_str/liblib_string.so

.PHONY : my_str/CMakeFiles/lib_string-shared.dir/build

my_str/CMakeFiles/lib_string-shared.dir/clean:
	cd /home/anastasiia/StringLibrary/cmake-build-debug/my_str && $(CMAKE_COMMAND) -P CMakeFiles/lib_string-shared.dir/cmake_clean.cmake
.PHONY : my_str/CMakeFiles/lib_string-shared.dir/clean

my_str/CMakeFiles/lib_string-shared.dir/depend:
	cd /home/anastasiia/StringLibrary/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anastasiia/StringLibrary /home/anastasiia/StringLibrary/my_str /home/anastasiia/StringLibrary/cmake-build-debug /home/anastasiia/StringLibrary/cmake-build-debug/my_str /home/anastasiia/StringLibrary/cmake-build-debug/my_str/CMakeFiles/lib_string-shared.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : my_str/CMakeFiles/lib_string-shared.dir/depend

