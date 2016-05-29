cmake_minimum_required(VERSION 3.2)


#set(CMAKE_CXX_COMPILER clang++)

set(pNAME "udr")
set(pVERSION "0.1.0")

project(${pNAME} CXX)
enable_testing()



find_package(Boost 1.60.0 EXACT REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
