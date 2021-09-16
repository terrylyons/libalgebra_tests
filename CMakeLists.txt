cmake_minimum_required(VERSION 3.12)


project(LibAlgebraUnitTests VERSION 1.0)


if(WIN32)
## better remove this and add it to the command line as machine specific
#list(APPEND CMAKE_MODULE_PATH  "c:/dev/vcpkg/scripts/buildsystems/")
    add_compile_options(/bigobj /fp:strict)
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

message(STATUS ">>> Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
message(STATUS ">>> UnitTest++_INCLUDE_DIRS = ${UnitTest++_INCLUDE_DIRS}")
message(STATUS ">>> OpenMP_CXX_INCLUDE_DIRS = ${OpenMP_CXX_INCLUDE_DIRS}")
message(STATUS ">>> OpenMP_CXX_FLAGS = ${OpenMP_CXX_FLAGS}")
message(STATUS ">>> Boost libraries: ${Boost_LIBRARIES}")
message(STATUS ">>> Bignum library: ${Bignum_LIBRARY}")


add_subdirectory(libalgebra)
add_subdirectory(LibAlgebraUnitTests)

add_executable(all_tests LibAlgebraUnitTests/LibAlgebraUnitTests.cpp)
target_link_libraries(all_tests PRIVATE
        integration_tests
        algebra_tests
        lie_tests
        signature_tests
        tensor_tests
        utils_tests
        vector_tests
        hall_set_tests
        )