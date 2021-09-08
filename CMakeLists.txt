cmake_minimum_required(VERSION 3.12)

#set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LibAlgebraUnitTests VERSION 1.0)
#set(CMAKE_CXX_FLAGS "-g -p -pg -fno-omit-frame-pointer -Wall ${CMAKE_CXX_FLAGS}")

#set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funroll-loops")


if(WIN32)
## better remove this and add it to the command line as machine specific
#list(APPEND CMAKE_MODULE_PATH  "c:/dev/vcpkg/scripts/buildsystems/")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:strict")
else()
endif()

include(vcpkg OPTIONAL)

find_package(UnitTest++ CONFIG REQUIRED)
if((NOT DEFINED UnitTest++_INCLUDE_DIRS) AND (DEFINED UTPP_INCLUDE_DIRS))
set(UnitTest++_INCLUDE_DIRS  "${UTPP_INCLUDE_DIRS}")
## have corrected the UnitTest++Config.cmake file to point UnitTest++_INCLUDE_DIRS to the correct path for the headers
endif()

find_package(Boost COMPONENTS thread filesystem iostreams chrono random container REQUIRED)

if(WIN32)
# for Windows operating system in general
# https://github.com/Microsoft/vcpkg/issues/2979
# this picks up the debug verson of mpir - the files have the fix.
find_library(Bignum_LIBRARY mpir)
else()
# otherwise
find_library(Bignum_LIBRARY gmp)
endif()

find_package(OpenMP)
if(OpenMP_CXX_FOUND AND MSVC)
## overwrite the windows flag -openmp -> -openmp:experimental to get simd
set( OpenMP_CXX_FLAGS "-openmp:experimental")
set_property(TARGET OpenMP::OpenMP_CXX
             PROPERTY INTERFACE_COMPILE_OPTIONS ${OpenMP_CXX_FLAGS})
endif()
message(STATUS ">>> OpenMP_CXX_FLAGS = ${OpenMP_CXX_FLAGS}")

include_directories(libalgebra ${Boost_INCLUDE_DIRS} ${UnitTest++_INCLUDE_DIRS} ${OpenMP_CXX_INCLUDE_DIRS} )
message(STATUS  ">>> Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
message(STATUS ">>> UnitTest++_INCLUDE_DIRS = ${UnitTest++_INCLUDE_DIRS}")
message(STATUS ">>> OpenMP_CXX_INCLUDE_DIRS = ${OpenMP_CXX_INCLUDE_DIRS}")
message(STATUS ">>> Boost libraries: ${Boost_LIBRARIES}")
message(STATUS ">>> Bignum library: ${Bignum_LIBRARY}")

#include_directories(C:/Users/tlyons/source/vcpkg/installed/x64-windows/include)
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
        LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)

target_include_directories(test PRIVATE "${PROJECT_BINARY_DIR}")
target_link_libraries(test PRIVATE UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})
target_link_libraries(test PUBLIC OpenMP::OpenMP_CXX)

add_executable(test_tensor "LibAlgebraUnitTests/tensor/run_tests.cpp" ${TENSOR_TESTS} LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_tensor PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_tensor  PRIVATE UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})
target_link_libraries(test_tensor PUBLIC OpenMP::OpenMP_CXX)

add_executable(test_lie "LibAlgebraUnitTests/lie/run_tests.cpp" ${LIE_TESTS}
        LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_lie PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_lie  PRIVATE UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})
target_link_libraries(test_lie PUBLIC OpenMP::OpenMP_CXX)

add_executable(test_vector "LibAlgebraUnitTests/vector/run_tests.cpp" ${VECTOR_TESTS}
        LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_vector PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_vector PRIVATE  UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})
target_link_libraries(test_vector  PUBLIC OpenMP::OpenMP_CXX)

add_executable(test_utils "LibAlgebraUnitTests/utils/run_tests.cpp" ${UTIL_TESTS}
        LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_utils PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_utils PRIVATE  UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})
target_link_libraries(test_utils PUBLIC OpenMP::OpenMP_CXX)

add_executable(test_algebra "LibAlgebraUnitTests/utils/run_tests.cpp" ${ALGEBRA_TESTS}
        LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_algebra PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_algebra PRIVATE  UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})
target_link_libraries(test_algebra PUBLIC OpenMP::OpenMP_CXX)

add_executable(test_signatures "LibAlgebraUnitTests/signature_tests/run_tests.cpp" "LibAlgebraUnitTests/memfile.cpp"
        ${SIGNATURE_TESTS} LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_signatures PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_signatures PRIVATE  UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})
target_link_libraries(test_signatures PUBLIC OpenMP::OpenMP_CXX)