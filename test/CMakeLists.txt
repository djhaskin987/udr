include(CMakeParseArguments)

function(udr_add_test)
    set(options)
    set(oneValueArgs TEST)
    set(multiValueArgs OTHER_SOURCES FEATURES)
    cmake_parse_arguments(udr_add_test "${options}" "${oneValueArgs}"
        "${multiValueArgs}" ${ARGN} )
    string(REGEX REPLACE ";" " " sources "${udr_add_test_OTHER_SOURCES}")
    string(REGEX REPLACE " +" ";" sources_list "${sources}")
    set(udr_add_test_TARGET "${udr_add_test_TEST}")
    add_executable(
        ${udr_add_test_TARGET}
        ${CMAKE_CURRENT_SOURCE_DIR}/${udr_add_test_TEST}.cpp;${sources_list}
        )
    target_link_libraries(
        ${udr_add_test_TARGET}
        boost_unit_test_framework
        )
    set_target_properties(
        ${udr_add_test_TARGET}
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 11)

    target_include_directories(
        ${udr_add_test_TARGET}
        PRIVATE ${CMAKE_SOURCE_DIR}/src/
        PRIVATE ${CMAKE_SOURCE_DIR}/test/
        )
    add_test(
        NAME ${udr_add_test_TARGET}
        COMMAND ${udr_add_test_TARGET} --report_level=detailed --log_level=message
        )
endfunction()

udr_add_test(
    TEST test_name_spec
    OTHER_SOURCES
        ${CMAKE_SOURCE_DIR}/src/package.hpp
        ${CMAKE_SOURCE_DIR}/src/repository.hpp
        ${CMAKE_SOURCE_DIR}/src/spec.hpp
        ${CMAKE_SOURCE_DIR}/src/name_spec.hpp
        ${CMAKE_SOURCE_DIR}/test/mock_repository.hpp
        ${CMAKE_SOURCE_DIR}/test/mock_repository.cpp
        )

udr_add_test(
    TEST test_version_relation_spec
    OTHER_SOURCES
        ${CMAKE_SOURCE_DIR}/src/package.hpp
        ${CMAKE_SOURCE_DIR}/src/repository.hpp
        ${CMAKE_SOURCE_DIR}/src/spec.hpp
        ${CMAKE_SOURCE_DIR}/src/name_spec.hpp
        ${CMAKE_SOURCE_DIR}/src/version_relation_spec.hpp
        ${CMAKE_SOURCE_DIR}/test/mock_repository.hpp
        ${CMAKE_SOURCE_DIR}/test/mock_repository.cpp
        )


#udr_add_test(
#    TARGET test_resolver
#    OTHER_SOURCES
#        ${CMAKE_SOURCE_DIR}/src/resolver.hpp
#        ${CMAKE_SOURCE_DIR}/src/version.hpp
#        ${CMAKE_SOURCE_DIR}/src/map_repository.hpp
#        ${CMAKE_SOURCE_DIR}/src/int_version.hpp
#        ${CMAKE_SOURCE_DIR}/src/int_version.cpp
#    FEATURES
#        cxx_deleted_functions
#        cxx_defaulted_functions
#    )
