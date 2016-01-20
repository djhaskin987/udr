include_directories(../src/)
add_executable(test_gripe ${CMAKE_CURRENT_SOURCE_DIR}/test_gripe.cpp)
add_test(
    NAME test_gripe
    COMMAND test_gripe --report_level=detailed
    )
target_link_libraries(test_gripe boost_unit_test_framework)
