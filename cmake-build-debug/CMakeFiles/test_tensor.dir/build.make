# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sam/CLionProjects/libalgebra_tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sam/CLionProjects/libalgebra_tests/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/test_tensor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_tensor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_tensor.dir/flags.make

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.o: ../LibAlgebraUnitTests/tensor/run_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/run_tests.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/run_tests.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/run_tests.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.o: ../LibAlgebraUnitTests/tensor/test_basis.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_basis.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_basis.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_basis.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.o: ../LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.o: ../LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.o: ../LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.o: ../LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.o: ../LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.o: ../LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.o: ../LibAlgebraUnitTests/tensor/test_tensor_functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.o: ../LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.o: ../LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.s

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.o: CMakeFiles/test_tensor.dir/flags.make
CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.o: ../LibAlgebraUnitTests/reporter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.o -c /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/reporter.cpp

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/reporter.cpp > CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.i

CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CLionProjects/libalgebra_tests/LibAlgebraUnitTests/reporter.cpp -o CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.s

# Object files for target test_tensor
test_tensor_OBJECTS = \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.o" \
"CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.o"

# External object files for target test_tensor
test_tensor_EXTERNAL_OBJECTS =

test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/run_tests.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_basis.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_functions.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_dense_tensor_multiplication.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_functions.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_hybrid_tensor_multiplication.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_functions.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_sparse_tensor_multiplication.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_functions.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_multiplication.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/tensor/test_tensor_size_info.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/LibAlgebraUnitTests/reporter.cpp.o
test_tensor: CMakeFiles/test_tensor.dir/build.make
test_tensor: /usr/local/lib/libUnitTest++.a
test_tensor: /usr/lib/libgmp.so
test_tensor: /usr/lib/libboost_thread.so.1.76.0
test_tensor: /usr/lib/libboost_filesystem.so.1.76.0
test_tensor: /usr/lib/libboost_iostreams.so.1.76.0
test_tensor: /usr/lib/libboost_chrono.so.1.76.0
test_tensor: /usr/lib/libboost_random.so.1.76.0
test_tensor: /usr/lib/libboost_container.so.1.76.0
test_tensor: /usr/lib/libgomp.so
test_tensor: /usr/lib/libpthread.so
test_tensor: CMakeFiles/test_tensor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable test_tensor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_tensor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_tensor.dir/build: test_tensor

.PHONY : CMakeFiles/test_tensor.dir/build

CMakeFiles/test_tensor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_tensor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_tensor.dir/clean

CMakeFiles/test_tensor.dir/depend:
	cd /home/sam/CLionProjects/libalgebra_tests/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sam/CLionProjects/libalgebra_tests /home/sam/CLionProjects/libalgebra_tests /home/sam/CLionProjects/libalgebra_tests/cmake-build-debug /home/sam/CLionProjects/libalgebra_tests/cmake-build-debug /home/sam/CLionProjects/libalgebra_tests/cmake-build-debug/CMakeFiles/test_tensor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_tensor.dir/depend

