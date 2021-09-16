

add_library(hall_set_tests OBJECT
        test_extension_of_functions.cpp
        )

target_link_libraries(hall_set_tests PUBLIC UnitTest++ Libalgebra::Libalgebra reporter)

add_executable(hall_set_tests_exe run_tests.cpp)
target_link_libraries(hall_set_tests_exe PRIVATE hall_set_tests)

