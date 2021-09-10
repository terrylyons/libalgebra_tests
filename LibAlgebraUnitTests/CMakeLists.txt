

add_library(reporter STATIC
        reporter.cpp
        )
target_link_libraries(reporter PUBLIC UnitTest++)


add_subdirectory(algebra)
add_subdirectory(lie)
add_subdirectory(signature_tests)
add_subdirectory(tensor)
add_subdirectory(utils)
add_subdirectory(vector)


add_library(integration_tests OBJECT
        AlgebraFunctionsTests.cpp
        HallSetTests.cpp
        LatticePathTests.cpp
        makebm.cpp
        memfile.cpp
        OMPSigsTests.cpp
        speed_tests.cpp
        tests_libalgebra-demo.cpp
        tests_TENSOR_LIE_CBH_MAPS.cpp
        TreeBufferHelper.cpp
        x64sigs.cpp
        )

target_link_libraries(integration_tests PUBLIC UnitTest++ reporter Libalgebra::Libalgebra)
target_link_libraries(integration_tests PRIVATE
        Boost::boost
        Boost::filesystem
        Boost::iostreams
        Boost::random
        OpenMP::OpenMP_CXX
        )

add_executable(integration_tests_exe LibAlgebraUnitTests.cpp)
target_link_libraries(integration_tests_exe PRIVATE integration_tests)