# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc/build"

# Utility rule file for calc_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/calc_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/calc_autogen.dir/progress.make

CMakeFiles/calc_autogen: calc_autogen/timestamp

calc_autogen/timestamp: /Users/nikitapotapov/Qt/6.6.2/macos/./libexec/moc
calc_autogen/timestamp: /Users/nikitapotapov/Qt/6.6.2/macos/./libexec/uic
calc_autogen/timestamp: CMakeFiles/calc_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target calc"
	/usr/local/Cellar/cmake/3.30.5/bin/cmake -E cmake_autogen "/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc/build/CMakeFiles/calc_autogen.dir/AutogenInfo.json" ""
	/usr/local/Cellar/cmake/3.30.5/bin/cmake -E touch "/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc/build/calc_autogen/timestamp"

calc_autogen: CMakeFiles/calc_autogen
calc_autogen: calc_autogen/timestamp
calc_autogen: CMakeFiles/calc_autogen.dir/build.make
.PHONY : calc_autogen

# Rule to build all files generated by this target.
CMakeFiles/calc_autogen.dir/build: calc_autogen
.PHONY : CMakeFiles/calc_autogen.dir/build

CMakeFiles/calc_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/calc_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/calc_autogen.dir/clean

CMakeFiles/calc_autogen.dir/depend:
	cd "/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc" "/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc" "/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc/build" "/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc/build" "/Users/nikitapotapov/Documents/Документы — MacBook Pro — Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc/build/CMakeFiles/calc_autogen.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/calc_autogen.dir/depend

