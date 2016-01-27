include(CMakeParseArguments)
include_directories(../src/)

function(add_udr_test)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs OTHER_SOURCES)
    cmake_parse_arguments(add_udr_test "${options}" "${oneValueArgs}"
        "${multiValueArgs}" ${ARGN} )
    string(REGEX REPLACE ";" " " sources "${add_udr_test_OTHER_SOURCES}")
    add_executable(
        ${add_udr_test_TARGET}
        ${CMAKE_CURRENT_SOURCE_DIR}/${add_udr_test_TARGET}.cpp
        ${sources}
        )
    add_test(
        NAME ${add_udr_test_TARGET}k
        COMMAND ${add_udr_test_TARGET} --report_level=detailed
        )
    target_link_libraries(
        ${add_udr_test_TARGET}
        boost_unit_test_framework
        )
    target_compile_features(
        ${add_udr_test_TARGET}
        PRIVATE cxx_nullptr cxx_noexcept
        )
endfunction()

add_udr_test(
    TARGET TestVersionClasses
    OTHER_SOURCES ${CMAKE_SOURCE_DIR}/src/IntegerVersion.cpp
    )
add_udr_test(
    TARGET TestNameClasses
    OTHER_SOURCES ${CMAKE_SOURCE_DIR}/src/StringName.cpp
    )
