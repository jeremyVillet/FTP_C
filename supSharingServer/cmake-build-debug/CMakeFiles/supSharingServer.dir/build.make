# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.1.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.1.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Documents\FTP C\supSharingServer"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Documents\FTP C\supSharingServer\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/supSharingServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/supSharingServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/supSharingServer.dir/flags.make

CMakeFiles/supSharingServer.dir/main.c.obj: CMakeFiles/supSharingServer.dir/flags.make
CMakeFiles/supSharingServer.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Documents\FTP C\supSharingServer\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/supSharingServer.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\supSharingServer.dir\main.c.obj   -c "C:\Documents\FTP C\supSharingServer\main.c"

CMakeFiles/supSharingServer.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/supSharingServer.dir/main.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Documents\FTP C\supSharingServer\main.c" > CMakeFiles\supSharingServer.dir\main.c.i

CMakeFiles/supSharingServer.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/supSharingServer.dir/main.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Documents\FTP C\supSharingServer\main.c" -o CMakeFiles\supSharingServer.dir\main.c.s

CMakeFiles/supSharingServer.dir/main.c.obj.requires:

.PHONY : CMakeFiles/supSharingServer.dir/main.c.obj.requires

CMakeFiles/supSharingServer.dir/main.c.obj.provides: CMakeFiles/supSharingServer.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\supSharingServer.dir\build.make CMakeFiles/supSharingServer.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/supSharingServer.dir/main.c.obj.provides

CMakeFiles/supSharingServer.dir/main.c.obj.provides.build: CMakeFiles/supSharingServer.dir/main.c.obj


# Object files for target supSharingServer
supSharingServer_OBJECTS = \
"CMakeFiles/supSharingServer.dir/main.c.obj"

# External object files for target supSharingServer
supSharingServer_EXTERNAL_OBJECTS =

supSharingServer.exe: CMakeFiles/supSharingServer.dir/main.c.obj
supSharingServer.exe: CMakeFiles/supSharingServer.dir/build.make
supSharingServer.exe: CMakeFiles/supSharingServer.dir/linklibs.rsp
supSharingServer.exe: CMakeFiles/supSharingServer.dir/objects1.rsp
supSharingServer.exe: CMakeFiles/supSharingServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Documents\FTP C\supSharingServer\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable supSharingServer.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\supSharingServer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/supSharingServer.dir/build: supSharingServer.exe

.PHONY : CMakeFiles/supSharingServer.dir/build

CMakeFiles/supSharingServer.dir/requires: CMakeFiles/supSharingServer.dir/main.c.obj.requires

.PHONY : CMakeFiles/supSharingServer.dir/requires

CMakeFiles/supSharingServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\supSharingServer.dir\cmake_clean.cmake
.PHONY : CMakeFiles/supSharingServer.dir/clean

CMakeFiles/supSharingServer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Documents\FTP C\supSharingServer" "C:\Documents\FTP C\supSharingServer" "C:\Documents\FTP C\supSharingServer\cmake-build-debug" "C:\Documents\FTP C\supSharingServer\cmake-build-debug" "C:\Documents\FTP C\supSharingServer\cmake-build-debug\CMakeFiles\supSharingServer.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/supSharingServer.dir/depend
