cmake_minimum_required(VERSION 3.10)

#set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD 11)

project(LibAlgebraUnitTests VERSION 1.0)
#set(CMAKE_CXX_FLAGS "-g -p -pg -fno-omit-frame-pointer -Wall ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -openmp:experimental")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
#set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funroll-loops")

find_package(UnitTest++ CONFIG REQUIRED)
if(DEFINED UTPP_INCLUDE_DIRS)
set(UnitTest++_INCLUDE_DIRS "${UTPP_INCLUDE_DIRS}")
## correct the Config.cmake file to point to the correct path for the header
endif()

find_package(Boost COMPONENTS thread filesystem iostreams chrono random REQUIRED)

if(WIN32)
# for Windows operating system in general
find_library(Bignum_LIBRARY mpir "C:/Users/tlyons/source/vcpkg/installed/x64-windows/lib")
else()
# otherwise
find_library(Bignum_LIBRARY gmp)
endif()

include_directories(libalgebra ${Boost_INCLUDE_DIRS} ${UnitTest++_INCLUDE_DIRS})
message(STATUS ">>> Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
message(STATUS ">>> UnitTest++_INCLUDE_DIRS = ${UnitTest++_INCLUDE_DIRS}")

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
        LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h "LibAlgebraUnitTests/tensor/sandbox.cpp")
target_include_directories(test PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})


add_executable(test_tensor "LibAlgebraUnitTests/tensor/run_tests.cpp" ${TENSOR_TESTS} LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_tensor PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_tensor  UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})


add_executable(test_lie "LibAlgebraUnitTests/lie/run_tests.cpp" ${LIE_TESTS}
        LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_lie PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_lie  UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})

add_executable(test_vector "LibAlgebraUnitTests/vector/run_tests.cpp" ${VECTOR_TESTS}
        LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_vector PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_vector  UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})

add_executable(test_utils "LibAlgebraUnitTests/utils/run_tests.cpp" ${UTIL_TESTS}
        LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_utils PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_utils  UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})

add_executable(test_algebra "LibAlgebraUnitTests/utils/run_tests.cpp" ${ALGEBRA_TESTS}
        LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_algebra PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_algebra  UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})

add_executable(test_signatures "LibAlgebraUnitTests/signature_tests/run_tests.cpp" "LibAlgebraUnitTests/memfile.cpp"
        ${SIGNATURE_TESTS} LibAlgebraUnitTests/reporter.cpp LibAlgebraUnitTests/reporter.h)
target_include_directories(test_signatures PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_signatures  UnitTest++ "${Bignum_LIBRARY}" ${Boost_LIBRARIES})