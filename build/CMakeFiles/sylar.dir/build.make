# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/illidan/file/cppfile/firstProject/sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/illidan/file/cppfile/firstProject/sylar/build

# Include any dependencies generated for this target.
include CMakeFiles/sylar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sylar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sylar.dir/flags.make

CMakeFiles/sylar.dir/log.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/log.cc.o: ../log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/illidan/file/cppfile/firstProject/sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sylar.dir/log.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/log.cc.o -c /home/illidan/file/cppfile/firstProject/sylar/log.cc

CMakeFiles/sylar.dir/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/illidan/file/cppfile/firstProject/sylar/log.cc > CMakeFiles/sylar.dir/log.cc.i

CMakeFiles/sylar.dir/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/illidan/file/cppfile/firstProject/sylar/log.cc -o CMakeFiles/sylar.dir/log.cc.s

CMakeFiles/sylar.dir/log.cc.o.requires:

.PHONY : CMakeFiles/sylar.dir/log.cc.o.requires

CMakeFiles/sylar.dir/log.cc.o.provides: CMakeFiles/sylar.dir/log.cc.o.requires
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/log.cc.o.provides.build
.PHONY : CMakeFiles/sylar.dir/log.cc.o.provides

CMakeFiles/sylar.dir/log.cc.o.provides.build: CMakeFiles/sylar.dir/log.cc.o


CMakeFiles/sylar.dir/util.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/util.cc.o: ../util.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/illidan/file/cppfile/firstProject/sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sylar.dir/util.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/util.cc.o -c /home/illidan/file/cppfile/firstProject/sylar/util.cc

CMakeFiles/sylar.dir/util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/util.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/illidan/file/cppfile/firstProject/sylar/util.cc > CMakeFiles/sylar.dir/util.cc.i

CMakeFiles/sylar.dir/util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/util.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/illidan/file/cppfile/firstProject/sylar/util.cc -o CMakeFiles/sylar.dir/util.cc.s

CMakeFiles/sylar.dir/util.cc.o.requires:

.PHONY : CMakeFiles/sylar.dir/util.cc.o.requires

CMakeFiles/sylar.dir/util.cc.o.provides: CMakeFiles/sylar.dir/util.cc.o.requires
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/util.cc.o.provides.build
.PHONY : CMakeFiles/sylar.dir/util.cc.o.provides

CMakeFiles/sylar.dir/util.cc.o.provides.build: CMakeFiles/sylar.dir/util.cc.o


CMakeFiles/sylar.dir/config.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/config.cc.o: ../config.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/illidan/file/cppfile/firstProject/sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sylar.dir/config.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/config.cc.o -c /home/illidan/file/cppfile/firstProject/sylar/config.cc

CMakeFiles/sylar.dir/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/config.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/illidan/file/cppfile/firstProject/sylar/config.cc > CMakeFiles/sylar.dir/config.cc.i

CMakeFiles/sylar.dir/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/config.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/illidan/file/cppfile/firstProject/sylar/config.cc -o CMakeFiles/sylar.dir/config.cc.s

CMakeFiles/sylar.dir/config.cc.o.requires:

.PHONY : CMakeFiles/sylar.dir/config.cc.o.requires

CMakeFiles/sylar.dir/config.cc.o.provides: CMakeFiles/sylar.dir/config.cc.o.requires
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/config.cc.o.provides.build
.PHONY : CMakeFiles/sylar.dir/config.cc.o.provides

CMakeFiles/sylar.dir/config.cc.o.provides.build: CMakeFiles/sylar.dir/config.cc.o


CMakeFiles/sylar.dir/thread.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/thread.cc.o: ../thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/illidan/file/cppfile/firstProject/sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sylar.dir/thread.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/thread.cc.o -c /home/illidan/file/cppfile/firstProject/sylar/thread.cc

CMakeFiles/sylar.dir/thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/thread.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/illidan/file/cppfile/firstProject/sylar/thread.cc > CMakeFiles/sylar.dir/thread.cc.i

CMakeFiles/sylar.dir/thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/thread.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/illidan/file/cppfile/firstProject/sylar/thread.cc -o CMakeFiles/sylar.dir/thread.cc.s

CMakeFiles/sylar.dir/thread.cc.o.requires:

.PHONY : CMakeFiles/sylar.dir/thread.cc.o.requires

CMakeFiles/sylar.dir/thread.cc.o.provides: CMakeFiles/sylar.dir/thread.cc.o.requires
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/thread.cc.o.provides.build
.PHONY : CMakeFiles/sylar.dir/thread.cc.o.provides

CMakeFiles/sylar.dir/thread.cc.o.provides.build: CMakeFiles/sylar.dir/thread.cc.o


# Object files for target sylar
sylar_OBJECTS = \
"CMakeFiles/sylar.dir/log.cc.o" \
"CMakeFiles/sylar.dir/util.cc.o" \
"CMakeFiles/sylar.dir/config.cc.o" \
"CMakeFiles/sylar.dir/thread.cc.o"

# External object files for target sylar
sylar_EXTERNAL_OBJECTS =

libsylar.so: CMakeFiles/sylar.dir/log.cc.o
libsylar.so: CMakeFiles/sylar.dir/util.cc.o
libsylar.so: CMakeFiles/sylar.dir/config.cc.o
libsylar.so: CMakeFiles/sylar.dir/thread.cc.o
libsylar.so: CMakeFiles/sylar.dir/build.make
libsylar.so: CMakeFiles/sylar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/illidan/file/cppfile/firstProject/sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libsylar.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sylar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sylar.dir/build: libsylar.so

.PHONY : CMakeFiles/sylar.dir/build

CMakeFiles/sylar.dir/requires: CMakeFiles/sylar.dir/log.cc.o.requires
CMakeFiles/sylar.dir/requires: CMakeFiles/sylar.dir/util.cc.o.requires
CMakeFiles/sylar.dir/requires: CMakeFiles/sylar.dir/config.cc.o.requires
CMakeFiles/sylar.dir/requires: CMakeFiles/sylar.dir/thread.cc.o.requires

.PHONY : CMakeFiles/sylar.dir/requires

CMakeFiles/sylar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sylar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sylar.dir/clean

CMakeFiles/sylar.dir/depend:
	cd /home/illidan/file/cppfile/firstProject/sylar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/illidan/file/cppfile/firstProject/sylar /home/illidan/file/cppfile/firstProject/sylar /home/illidan/file/cppfile/firstProject/sylar/build /home/illidan/file/cppfile/firstProject/sylar/build /home/illidan/file/cppfile/firstProject/sylar/build/CMakeFiles/sylar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sylar.dir/depend
