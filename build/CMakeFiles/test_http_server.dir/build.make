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
CMAKE_SOURCE_DIR = /home/illidan/file/cppfile/firstProject/new/sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/illidan/file/cppfile/firstProject/new/sylar/build

# Include any dependencies generated for this target.
include CMakeFiles/test_http_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_http_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_http_server.dir/flags.make

CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o: CMakeFiles/test_http_server.dir/flags.make
CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o: ../test/test_http_sever.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/illidan/file/cppfile/firstProject/new/sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o -c /home/illidan/file/cppfile/firstProject/new/sylar/test/test_http_sever.cc

CMakeFiles/test_http_server.dir/test/test_http_sever.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_http_server.dir/test/test_http_sever.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/illidan/file/cppfile/firstProject/new/sylar/test/test_http_sever.cc > CMakeFiles/test_http_server.dir/test/test_http_sever.cc.i

CMakeFiles/test_http_server.dir/test/test_http_sever.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_http_server.dir/test/test_http_sever.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/illidan/file/cppfile/firstProject/new/sylar/test/test_http_sever.cc -o CMakeFiles/test_http_server.dir/test/test_http_sever.cc.s

CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o.requires:

.PHONY : CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o.requires

CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o.provides: CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o.requires
	$(MAKE) -f CMakeFiles/test_http_server.dir/build.make CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o.provides.build
.PHONY : CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o.provides

CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o.provides.build: CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o


# Object files for target test_http_server
test_http_server_OBJECTS = \
"CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o"

# External object files for target test_http_server
test_http_server_EXTERNAL_OBJECTS =

test_http_server: CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o
test_http_server: CMakeFiles/test_http_server.dir/build.make
test_http_server: libsylar.so
test_http_server: CMakeFiles/test_http_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/illidan/file/cppfile/firstProject/new/sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_http_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_http_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_http_server.dir/build: test_http_server

.PHONY : CMakeFiles/test_http_server.dir/build

CMakeFiles/test_http_server.dir/requires: CMakeFiles/test_http_server.dir/test/test_http_sever.cc.o.requires

.PHONY : CMakeFiles/test_http_server.dir/requires

CMakeFiles/test_http_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_http_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_http_server.dir/clean

CMakeFiles/test_http_server.dir/depend:
	cd /home/illidan/file/cppfile/firstProject/new/sylar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/illidan/file/cppfile/firstProject/new/sylar /home/illidan/file/cppfile/firstProject/new/sylar /home/illidan/file/cppfile/firstProject/new/sylar/build /home/illidan/file/cppfile/firstProject/new/sylar/build /home/illidan/file/cppfile/firstProject/new/sylar/build/CMakeFiles/test_http_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_http_server.dir/depend

