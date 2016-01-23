include_directories(../src/)
add_executable(TestIntegerVersion
    ${CMAKE_CURRENT_SOURCE_DIR}/TestIntegerVersion.cpp
    ${CMAKE_SOURCE_DIR}/src/IntegerVersion.cpp)
add_test(
    NAME TestIntegerVersion
    COMMAND TestIntegerVersion --report_level=detailed
    )
target_link_libraries(TestIntegerVersion boost_unit_test_framework)
target_compile_features(TestIntegerVersion PRIVATE cxx_nullptr cxx_noexcept)
