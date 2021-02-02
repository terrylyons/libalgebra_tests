cmake_minimum_required(VERSION 3.10)


project(LibAlgebraUnitTests VERSION 1.0)

find_package(UnitTest++ REQUIRED)
find_package(Boost COMPONENTS filesystem iostreams REQUIRED)

include_directories(libalgebra)

file(GLOB SOURCES "LibAlgebraUnitTests/*.cpp")
file(GLOB TENSOR_TESTS "LibAlgebraUnitTests/tensor/test_*.cpp")
file(GLOB LIE_TESTS "LibAlgebraUnitTests/lie/test_*.cpp")

add_executable(test ${SOURCES}
        ${TENSOR_TESTS}
        ${LIE_TESTS}
        )
target_include_directories(test PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test pthread UnitTest++ gmp ${Boost_LIBRARIES})


add_executable(test_tensor "LibAlgebraUnitTests/tensor/run_tests.cpp" ${TENSOR_TESTS})
target_include_directories(test_tensor PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_tensor pthread UnitTest++ gmp ${Boost_LIBRARIES})


add_executable(test_lie "LibAlgebraUnitTests/lie/run_tests.cpp" ${LIE_TESTS})
target_include_directories(test_lie PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_lie pthread UnitTest++ gmp ${Boost_LIBRARIES})