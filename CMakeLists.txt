cmake_minimum_required(VERSION 3.5)

project(LaptimerCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

option(ENABLE_TEST "Enable unit tests" OFF)
option(ENABLE_CATCH2_FETCH "This option enables that catch2 is fetched in configuration" OFF)
option(ENABLE_KDBINDINGS_FETCH "This option enables that KDBindings is fetched in configuration" ON)

add_subdirectory(src)

if(ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif(ENABLE_TEST)
