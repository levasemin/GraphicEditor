# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild

# Utility rule file for pluginstandart-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/pluginstandart-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pluginstandart-populate.dir/progress.make

CMakeFiles/pluginstandart-populate: CMakeFiles/pluginstandart-populate-complete

CMakeFiles/pluginstandart-populate-complete: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-install
CMakeFiles/pluginstandart-populate-complete: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-mkdir
CMakeFiles/pluginstandart-populate-complete: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-download
CMakeFiles/pluginstandart-populate-complete: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-update
CMakeFiles/pluginstandart-populate-complete: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-patch
CMakeFiles/pluginstandart-populate-complete: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-configure
CMakeFiles/pluginstandart-populate-complete: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-build
CMakeFiles/pluginstandart-populate-complete: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-install
CMakeFiles/pluginstandart-populate-complete: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'pluginstandart-populate'"
	/usr/bin/cmake -E make_directory /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles
	/usr/bin/cmake -E touch /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles/pluginstandart-populate-complete
	/usr/bin/cmake -E touch /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-done

pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-update:
.PHONY : pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-update

pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-build: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'pluginstandart-populate'"
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-build && /usr/bin/cmake -E echo_append
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-build && /usr/bin/cmake -E touch /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-build

pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-configure: pluginstandart-populate-prefix/tmp/pluginstandart-populate-cfgcmd.txt
pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-configure: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'pluginstandart-populate'"
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-build && /usr/bin/cmake -E echo_append
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-build && /usr/bin/cmake -E touch /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-configure

pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-download: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-gitinfo.txt
pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-download: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'pluginstandart-populate'"
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps && /usr/bin/cmake -P /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/tmp/pluginstandart-populate-gitclone.cmake
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps && /usr/bin/cmake -E touch /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-download

pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-install: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'pluginstandart-populate'"
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-build && /usr/bin/cmake -E echo_append
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-build && /usr/bin/cmake -E touch /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-install

pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'pluginstandart-populate'"
	/usr/bin/cmake -Dcfgdir= -P /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/tmp/pluginstandart-populate-mkdirs.cmake
	/usr/bin/cmake -E touch /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-mkdir

pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-patch: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'pluginstandart-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-patch

pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-update:
.PHONY : pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-update

pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-test: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'pluginstandart-populate'"
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-build && /usr/bin/cmake -E echo_append
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-build && /usr/bin/cmake -E touch /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-test

pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-update: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'pluginstandart-populate'"
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-src && /usr/bin/cmake -P /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/tmp/pluginstandart-populate-gitupdate.cmake

pluginstandart-populate: CMakeFiles/pluginstandart-populate
pluginstandart-populate: CMakeFiles/pluginstandart-populate-complete
pluginstandart-populate: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-build
pluginstandart-populate: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-configure
pluginstandart-populate: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-download
pluginstandart-populate: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-install
pluginstandart-populate: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-mkdir
pluginstandart-populate: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-patch
pluginstandart-populate: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-test
pluginstandart-populate: pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/pluginstandart-populate-update
pluginstandart-populate: CMakeFiles/pluginstandart-populate.dir/build.make
.PHONY : pluginstandart-populate

# Rule to build all files generated by this target.
CMakeFiles/pluginstandart-populate.dir/build: pluginstandart-populate
.PHONY : CMakeFiles/pluginstandart-populate.dir/build

CMakeFiles/pluginstandart-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pluginstandart-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pluginstandart-populate.dir/clean

CMakeFiles/pluginstandart-populate.dir/depend:
	cd /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild /home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/CMakeFiles/pluginstandart-populate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pluginstandart-populate.dir/depend

