# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cai/CLionProjects/SPL-Compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cai/CLionProjects/SPL-Compiler

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CLion.app/Contents/bin/cmake/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/Applications/CLion.app/Contents/bin/cmake/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/cai/CLionProjects/SPL-Compiler/CMakeFiles /Users/cai/CLionProjects/SPL-Compiler/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/cai/CLionProjects/SPL-Compiler/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named SPL_Compiler

# Build rule for target.
SPL_Compiler: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 SPL_Compiler
.PHONY : SPL_Compiler

# fast build rule for target.
SPL_Compiler/fast:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/build
.PHONY : SPL_Compiler/fast

absyn.o: absyn.c.o

.PHONY : absyn.o

# target to build an object file
absyn.c.o:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/absyn.c.o
.PHONY : absyn.c.o

absyn.i: absyn.c.i

.PHONY : absyn.i

# target to preprocess a source file
absyn.c.i:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/absyn.c.i
.PHONY : absyn.c.i

absyn.s: absyn.c.s

.PHONY : absyn.s

# target to generate assembly for a file
absyn.c.s:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/absyn.c.s
.PHONY : absyn.c.s

errormsg.o: errormsg.c.o

.PHONY : errormsg.o

# target to build an object file
errormsg.c.o:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/errormsg.c.o
.PHONY : errormsg.c.o

errormsg.i: errormsg.c.i

.PHONY : errormsg.i

# target to preprocess a source file
errormsg.c.i:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/errormsg.c.i
.PHONY : errormsg.c.i

errormsg.s: errormsg.c.s

.PHONY : errormsg.s

# target to generate assembly for a file
errormsg.c.s:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/errormsg.c.s
.PHONY : errormsg.c.s

lex.yy.o: lex.yy.c.o

.PHONY : lex.yy.o

# target to build an object file
lex.yy.c.o:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/lex.yy.c.o
.PHONY : lex.yy.c.o

lex.yy.i: lex.yy.c.i

.PHONY : lex.yy.i

# target to preprocess a source file
lex.yy.c.i:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/lex.yy.c.i
.PHONY : lex.yy.c.i

lex.yy.s: lex.yy.c.s

.PHONY : lex.yy.s

# target to generate assembly for a file
lex.yy.c.s:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/lex.yy.c.s
.PHONY : lex.yy.c.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/main.cpp.s
.PHONY : main.cpp.s

prabsyn.o: prabsyn.c.o

.PHONY : prabsyn.o

# target to build an object file
prabsyn.c.o:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/prabsyn.c.o
.PHONY : prabsyn.c.o

prabsyn.i: prabsyn.c.i

.PHONY : prabsyn.i

# target to preprocess a source file
prabsyn.c.i:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/prabsyn.c.i
.PHONY : prabsyn.c.i

prabsyn.s: prabsyn.c.s

.PHONY : prabsyn.s

# target to generate assembly for a file
prabsyn.c.s:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/prabsyn.c.s
.PHONY : prabsyn.c.s

symbol.o: symbol.c.o

.PHONY : symbol.o

# target to build an object file
symbol.c.o:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/symbol.c.o
.PHONY : symbol.c.o

symbol.i: symbol.c.i

.PHONY : symbol.i

# target to preprocess a source file
symbol.c.i:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/symbol.c.i
.PHONY : symbol.c.i

symbol.s: symbol.c.s

.PHONY : symbol.s

# target to generate assembly for a file
symbol.c.s:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/symbol.c.s
.PHONY : symbol.c.s

table.o: table.c.o

.PHONY : table.o

# target to build an object file
table.c.o:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/table.c.o
.PHONY : table.c.o

table.i: table.c.i

.PHONY : table.i

# target to preprocess a source file
table.c.i:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/table.c.i
.PHONY : table.c.i

table.s: table.c.s

.PHONY : table.s

# target to generate assembly for a file
table.c.s:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/table.c.s
.PHONY : table.c.s

util.o: util.c.o

.PHONY : util.o

# target to build an object file
util.c.o:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/util.c.o
.PHONY : util.c.o

util.i: util.c.i

.PHONY : util.i

# target to preprocess a source file
util.c.i:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/util.c.i
.PHONY : util.c.i

util.s: util.c.s

.PHONY : util.s

# target to generate assembly for a file
util.c.s:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/util.c.s
.PHONY : util.c.s

y.tab.o: y.tab.c.o

.PHONY : y.tab.o

# target to build an object file
y.tab.c.o:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/y.tab.c.o
.PHONY : y.tab.c.o

y.tab.i: y.tab.c.i

.PHONY : y.tab.i

# target to preprocess a source file
y.tab.c.i:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/y.tab.c.i
.PHONY : y.tab.c.i

y.tab.s: y.tab.c.s

.PHONY : y.tab.s

# target to generate assembly for a file
y.tab.c.s:
	$(MAKE) -f CMakeFiles/SPL_Compiler.dir/build.make CMakeFiles/SPL_Compiler.dir/y.tab.c.s
.PHONY : y.tab.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... SPL_Compiler"
	@echo "... absyn.o"
	@echo "... absyn.i"
	@echo "... absyn.s"
	@echo "... errormsg.o"
	@echo "... errormsg.i"
	@echo "... errormsg.s"
	@echo "... lex.yy.o"
	@echo "... lex.yy.i"
	@echo "... lex.yy.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... prabsyn.o"
	@echo "... prabsyn.i"
	@echo "... prabsyn.s"
	@echo "... symbol.o"
	@echo "... symbol.i"
	@echo "... symbol.s"
	@echo "... table.o"
	@echo "... table.i"
	@echo "... table.s"
	@echo "... util.o"
	@echo "... util.i"
	@echo "... util.s"
	@echo "... y.tab.o"
	@echo "... y.tab.i"
	@echo "... y.tab.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

