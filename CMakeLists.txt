cmake_minimum_required(VERSION 3.10)


project(LibAlgebraUnitTests VERSION 1.0)

find_package(UnitTest++ REQUIRED)
find_package(Boost COMPONENTS filesystem iostreams REQUIRED)




include_directories(libalgebra)

file(GLOB SOURCES "LibAlgebraUnitTests/*.cpp")

configure_file(libalgebra_unittests.h.in unittest_config.h)


add_executable(test ${SOURCES})
target_include_directories(test PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test pthread UnitTest++ gmp ${Boost_LIBRARIES})


