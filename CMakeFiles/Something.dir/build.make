# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ec2-user/lit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ec2-user/lit

# Include any dependencies generated for this target.
include CMakeFiles/Something.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Something.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Something.dir/flags.make

CMakeFiles/Something.dir/Something.cpp.o: CMakeFiles/Something.dir/flags.make
CMakeFiles/Something.dir/Something.cpp.o: Something.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ec2-user/lit/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Something.dir/Something.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Something.dir/Something.cpp.o -c /home/ec2-user/lit/Something.cpp

CMakeFiles/Something.dir/Something.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Something.dir/Something.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ec2-user/lit/Something.cpp > CMakeFiles/Something.dir/Something.cpp.i

CMakeFiles/Something.dir/Something.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Something.dir/Something.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ec2-user/lit/Something.cpp -o CMakeFiles/Something.dir/Something.cpp.s

# Object files for target Something
Something_OBJECTS = \
"CMakeFiles/Something.dir/Something.cpp.o"

# External object files for target Something
Something_EXTERNAL_OBJECTS =

Something: CMakeFiles/Something.dir/Something.cpp.o
Something: CMakeFiles/Something.dir/build.make
Something: libFileWatcher.a
Something: CMakeFiles/Something.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ec2-user/lit/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Something"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Something.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Something.dir/build: Something

.PHONY : CMakeFiles/Something.dir/build

CMakeFiles/Something.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Something.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Something.dir/clean

CMakeFiles/Something.dir/depend:
	cd /home/ec2-user/lit && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ec2-user/lit /home/ec2-user/lit /home/ec2-user/lit /home/ec2-user/lit /home/ec2-user/lit/CMakeFiles/Something.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Something.dir/depend

