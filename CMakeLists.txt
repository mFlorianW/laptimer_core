cmake_minimum_required(VERSION 3.5)

project(LaptimerCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

option(ENABLE_TEST "Enable unit tests" OFF)
option(ENABLE_CATCH2_FETCH "This option enables that catch2 is fetched in configuration" OFF)
option(ENABLE_KDBINDINGS_FETCH "This option enables that KDBindings is fetched in configuration" ON)
option(ENABLE_ARDUINOJSON_FETCH "This option enables that ARDUIONJSON is fetched in configuration" ON)

if(ENABLE_KDBINDINGS_FETCH)
    FetchContent_Declare(
        KDBindings
        GIT_REPOSITORY https://github.com/KDAB/KDBindings.git
        GIT_TAG        37a49b3eaa64861464da8bc506dccecf7516101f
    )
    FetchContent_MakeAvailable(KDBindings)
    list(APPEND CMAKE_MODULE_PATH ${kdbindings_BUILD_DIR})
else()
find_package(KDBindings CONFIG REQUIRED)
endif()

if(ENABLE_ARDUINOJSON_FETCH)
    FetchContent_Declare(
        ArduinoJson
        GIT_REPOSITORY https://github.com/bblanchon/ArduinoJson.git
        GIT_TAG        v6.19.3
    )
    FetchContent_MakeAvailable(ArduinoJson)
    include_directories(SYSTEM ${arduinojson_SOURCE_DIR}/src)
endif()

add_subdirectory(src)

if(ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif(ENABLE_TEST)
