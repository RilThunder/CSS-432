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
CMAKE_COMMAND = /home/thuan/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4203.549/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/thuan/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4203.549/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thuan/CSS-432/HW1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thuan/CSS-432/HW1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HW1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW1.dir/flags.make

CMakeFiles/HW1.dir/Server.cpp.o: CMakeFiles/HW1.dir/flags.make
CMakeFiles/HW1.dir/Server.cpp.o: ../Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thuan/CSS-432/HW1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HW1.dir/Server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HW1.dir/Server.cpp.o -c /home/thuan/CSS-432/HW1/Server.cpp

CMakeFiles/HW1.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW1.dir/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thuan/CSS-432/HW1/Server.cpp > CMakeFiles/HW1.dir/Server.cpp.i

CMakeFiles/HW1.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW1.dir/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thuan/CSS-432/HW1/Server.cpp -o CMakeFiles/HW1.dir/Server.cpp.s

CMakeFiles/HW1.dir/Server.cpp.o.requires:

.PHONY : CMakeFiles/HW1.dir/Server.cpp.o.requires

CMakeFiles/HW1.dir/Server.cpp.o.provides: CMakeFiles/HW1.dir/Server.cpp.o.requires
	$(MAKE) -f CMakeFiles/HW1.dir/build.make CMakeFiles/HW1.dir/Server.cpp.o.provides.build
.PHONY : CMakeFiles/HW1.dir/Server.cpp.o.provides

CMakeFiles/HW1.dir/Server.cpp.o.provides.build: CMakeFiles/HW1.dir/Server.cpp.o


CMakeFiles/HW1.dir/Client.cpp.o: CMakeFiles/HW1.dir/flags.make
CMakeFiles/HW1.dir/Client.cpp.o: ../Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thuan/CSS-432/HW1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HW1.dir/Client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HW1.dir/Client.cpp.o -c /home/thuan/CSS-432/HW1/Client.cpp

CMakeFiles/HW1.dir/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW1.dir/Client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thuan/CSS-432/HW1/Client.cpp > CMakeFiles/HW1.dir/Client.cpp.i

CMakeFiles/HW1.dir/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW1.dir/Client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thuan/CSS-432/HW1/Client.cpp -o CMakeFiles/HW1.dir/Client.cpp.s

CMakeFiles/HW1.dir/Client.cpp.o.requires:

.PHONY : CMakeFiles/HW1.dir/Client.cpp.o.requires

CMakeFiles/HW1.dir/Client.cpp.o.provides: CMakeFiles/HW1.dir/Client.cpp.o.requires
	$(MAKE) -f CMakeFiles/HW1.dir/build.make CMakeFiles/HW1.dir/Client.cpp.o.provides.build
.PHONY : CMakeFiles/HW1.dir/Client.cpp.o.provides

CMakeFiles/HW1.dir/Client.cpp.o.provides.build: CMakeFiles/HW1.dir/Client.cpp.o


CMakeFiles/HW1.dir/ClientBenchMark.cpp.o: CMakeFiles/HW1.dir/flags.make
CMakeFiles/HW1.dir/ClientBenchMark.cpp.o: ../ClientBenchMark.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thuan/CSS-432/HW1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/HW1.dir/ClientBenchMark.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HW1.dir/ClientBenchMark.cpp.o -c /home/thuan/CSS-432/HW1/ClientBenchMark.cpp

CMakeFiles/HW1.dir/ClientBenchMark.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW1.dir/ClientBenchMark.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thuan/CSS-432/HW1/ClientBenchMark.cpp > CMakeFiles/HW1.dir/ClientBenchMark.cpp.i

CMakeFiles/HW1.dir/ClientBenchMark.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW1.dir/ClientBenchMark.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thuan/CSS-432/HW1/ClientBenchMark.cpp -o CMakeFiles/HW1.dir/ClientBenchMark.cpp.s

CMakeFiles/HW1.dir/ClientBenchMark.cpp.o.requires:

.PHONY : CMakeFiles/HW1.dir/ClientBenchMark.cpp.o.requires

CMakeFiles/HW1.dir/ClientBenchMark.cpp.o.provides: CMakeFiles/HW1.dir/ClientBenchMark.cpp.o.requires
	$(MAKE) -f CMakeFiles/HW1.dir/build.make CMakeFiles/HW1.dir/ClientBenchMark.cpp.o.provides.build
.PHONY : CMakeFiles/HW1.dir/ClientBenchMark.cpp.o.provides

CMakeFiles/HW1.dir/ClientBenchMark.cpp.o.provides.build: CMakeFiles/HW1.dir/ClientBenchMark.cpp.o


CMakeFiles/HW1.dir/ServerBenchMark.cpp.o: CMakeFiles/HW1.dir/flags.make
CMakeFiles/HW1.dir/ServerBenchMark.cpp.o: ../ServerBenchMark.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thuan/CSS-432/HW1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/HW1.dir/ServerBenchMark.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HW1.dir/ServerBenchMark.cpp.o -c /home/thuan/CSS-432/HW1/ServerBenchMark.cpp

CMakeFiles/HW1.dir/ServerBenchMark.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW1.dir/ServerBenchMark.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thuan/CSS-432/HW1/ServerBenchMark.cpp > CMakeFiles/HW1.dir/ServerBenchMark.cpp.i

CMakeFiles/HW1.dir/ServerBenchMark.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW1.dir/ServerBenchMark.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thuan/CSS-432/HW1/ServerBenchMark.cpp -o CMakeFiles/HW1.dir/ServerBenchMark.cpp.s

CMakeFiles/HW1.dir/ServerBenchMark.cpp.o.requires:

.PHONY : CMakeFiles/HW1.dir/ServerBenchMark.cpp.o.requires

CMakeFiles/HW1.dir/ServerBenchMark.cpp.o.provides: CMakeFiles/HW1.dir/ServerBenchMark.cpp.o.requires
	$(MAKE) -f CMakeFiles/HW1.dir/build.make CMakeFiles/HW1.dir/ServerBenchMark.cpp.o.provides.build
.PHONY : CMakeFiles/HW1.dir/ServerBenchMark.cpp.o.provides

CMakeFiles/HW1.dir/ServerBenchMark.cpp.o.provides.build: CMakeFiles/HW1.dir/ServerBenchMark.cpp.o


# Object files for target HW1
HW1_OBJECTS = \
"CMakeFiles/HW1.dir/Server.cpp.o" \
"CMakeFiles/HW1.dir/Client.cpp.o" \
"CMakeFiles/HW1.dir/ClientBenchMark.cpp.o" \
"CMakeFiles/HW1.dir/ServerBenchMark.cpp.o"

# External object files for target HW1
HW1_EXTERNAL_OBJECTS =

HW1: CMakeFiles/HW1.dir/Server.cpp.o
HW1: CMakeFiles/HW1.dir/Client.cpp.o
HW1: CMakeFiles/HW1.dir/ClientBenchMark.cpp.o
HW1: CMakeFiles/HW1.dir/ServerBenchMark.cpp.o
HW1: CMakeFiles/HW1.dir/build.make
HW1: CMakeFiles/HW1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thuan/CSS-432/HW1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable HW1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HW1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW1.dir/build: HW1

.PHONY : CMakeFiles/HW1.dir/build

CMakeFiles/HW1.dir/requires: CMakeFiles/HW1.dir/Server.cpp.o.requires
CMakeFiles/HW1.dir/requires: CMakeFiles/HW1.dir/Client.cpp.o.requires
CMakeFiles/HW1.dir/requires: CMakeFiles/HW1.dir/ClientBenchMark.cpp.o.requires
CMakeFiles/HW1.dir/requires: CMakeFiles/HW1.dir/ServerBenchMark.cpp.o.requires

.PHONY : CMakeFiles/HW1.dir/requires

CMakeFiles/HW1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HW1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HW1.dir/clean

CMakeFiles/HW1.dir/depend:
	cd /home/thuan/CSS-432/HW1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thuan/CSS-432/HW1 /home/thuan/CSS-432/HW1 /home/thuan/CSS-432/HW1/cmake-build-debug /home/thuan/CSS-432/HW1/cmake-build-debug /home/thuan/CSS-432/HW1/cmake-build-debug/CMakeFiles/HW1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW1.dir/depend

