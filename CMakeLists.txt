cmake_minimum_required(VERSION 3.10)

#set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD 11)

project(LibAlgebraUnitTests VERSION 1.0)
set(CMAKE_CXX_FLAGS "-g -p -pg -fno-omit-frame-pointer -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
#set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funroll-loops")

find_package(UnitTest++ REQUIRED)
find_package(Boost COMPONENTS filesystem iostreams chrono REQUIRED)

include_directories(libalgebra)

file(GLOB SOURCES           "LibAlgebraUnitTests/*.cpp")
file(GLOB TENSOR_TESTS      "LibAlgebraUnitTests/tensor/test_*.cpp")
file(GLOB LIE_TESTS         "LibAlgebraUnitTests/lie/test_*.cpp")
file(GLOB VECTOR_TESTS      "LibAlgebraUnitTests/vector/test_*.cpp")
file(GLOB UTIL_TESTS        "LibAlgebraUnitTests/utils/test_*.cpp")
file(GLOB ALGEBRA_TESTS     "LibAlgebraUnitTests/algebra/test_*.cpp")
file(GLOB SIGNATURE_TESTS   "LibAlgebraUnitTests/signature_tests/test_*.cpp")

add_executable(test ${SOURCES}
        ${TENSOR_TESTS}
        ${LIE_TESTS}
        ${VECTOR_TESTS}
        ${UTIL_TESTS}
        ${ALGEBRA_TESTS}
        ${SIGNATURE_TESTS}
        )
target_include_directories(test PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test pthread UnitTest++ gmp ${Boost_LIBRARIES})


add_executable(test_tensor "LibAlgebraUnitTests/tensor/run_tests.cpp" ${TENSOR_TESTS})
target_include_directories(test_tensor PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_tensor pthread UnitTest++ gmp ${Boost_LIBRARIES})


add_executable(test_lie "LibAlgebraUnitTests/lie/run_tests.cpp" ${LIE_TESTS})
target_include_directories(test_lie PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_lie pthread UnitTest++ gmp ${Boost_LIBRARIES})

add_executable(test_vector "LibAlgebraUnitTests/vector/run_tests.cpp" ${VECTOR_TESTS})
target_include_directories(test_vector PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_vector pthread UnitTest++ gmp ${Boost_LIBRARIES})

add_executable(test_utils "LibAlgebraUnitTests/utils/run_tests.cpp" ${UTIL_TESTS})
target_include_directories(test_utils PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_utils pthread UnitTest++ gmp ${Boost_LIBRARIES})

add_executable(test_algebra "LibAlgebraUnitTests/utils/run_tests.cpp" ${ALGEBRA_TESTS})
target_include_directories(test_algebra PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_algebra pthread UnitTest++ gmp ${Boost_LIBRARIES})

add_executable(test_signatures "LibAlgebraUnitTests/signature_tests/run_tests.cpp" "LibAlgebraUnitTests/memfile.cpp"
        ${SIGNATURE_TESTS})
target_include_directories(test_signatures PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_signatures pthread UnitTest++ gmp ${Boost_LIBRARIES})