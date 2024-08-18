cmake_minimum_required(VERSION 3.5)

project(LaptimerCore)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/configuration/cmake/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)
include(FeatureSummary)
include(CheckCCompilerFlag)
include(PreCommit)

option(ENABLE_TEST "Enable unit tests" OFF)
option(ENABLE_CATCH2_FETCH "This option enables that catch2 is fetched in configuration" OFF)
option(ENABLE_KDBINDINGS_FETCH "This option enables that KDBindings is fetched in configuration" ON)
option(ENABLE_ARDUINOJSON_FETCH "This option enables that ARDUIONJSON is fetched in configuration" ON)
option(ENABLE_LVGL_FETCH "This option enables that LVGL is fetched in configuration" ON)
option(ENABLE_QT "This option enables QT implementations" ON)
option(ENABLE_PRECOMMIT "Enables automatic pre-commit install." OFF)
option(ENABLE_BOOST "Enables the boost support" OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_feature_info(PreCommit ENABLE_PRECOMMIT "Automatic install of the Python pre-commit tool.")

if(ENABLE_PRECOMMIT)
    setup_precommit()
endif()


if(ENABLE_KDBINDINGS_FETCH)
    include(KDBindingsFetch)
    fetch_kdbindings()
else()
    find_package(KDBindings REQUIRED)
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

find_package(SDL2 REQUIRED)
if (ENABLE_LVGL_FETCH)
    include(LvglFetch)
    fetch_lvgl()
else()
    find_package(lvgl-ssd1322 REQUIRED)
    find_package(lvgl-ssd1322-drivers REQUIRED)
endif(ENABLE_LVGL_FETCH)

find_package(SQLite3 REQUIRED)
if(ENABLE_BOOST)
    find_package(Boost CONFIG)
endif()

check_c_compiler_flag(-Wall HAS_WALL)
if(HAS_WALL)
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()

add_subdirectory(libs)
add_subdirectory(db)
add_subdirectory(programs)

if(ENABLE_TEST)
    enable_testing()
    add_subdirectory(tests)
endif(ENABLE_TEST)

feature_summary(WHAT ALL)
