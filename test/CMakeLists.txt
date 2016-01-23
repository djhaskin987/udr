include_directories(../src/)
add_executable(TestAPIClasses
    ${CMAKE_CURRENT_SOURCE_DIR}/TestAPIClasses.cpp
    ${CMAKE_SOURCE_DIR}/src/IntegerVersion.cpp
    ${CMAKE_SOURCE_DIR}/src/StringName.cpp)
add_test(
    NAME TestAPIClasses
    COMMAND TestAPIClasses --report_level=detailed
    )
target_link_libraries(TestAPIClasses boost_unit_test_framework)
target_compile_features(TestAPIClasses PRIVATE cxx_nullptr cxx_noexcept)
