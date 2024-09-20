cmake_minimum_required(VERSION 3.19)

project(LaptimerCore)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/configuration/cmake/")

include(FeatureSummary)
include(CheckCCompilerFlag)
include(GNUInstallDirs)
include(PreCommit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SHARED_DATADIR ${CMAKE_INSTALL_DATAROOTDIR}/lappy)

option(ENABLE_TEST "Enable unit tests" OFF)
option(ENABLE_QT "This option enables QT implementations" ON)
option(ENABLE_PRECOMMIT "Enables automatic pre-commit install." OFF)
option(ENABLE_BOOST "Enables the boost support" OFF)
add_feature_info(PreCommit ENABLE_PRECOMMIT "Automatic install of the Python pre-commit tool.")

if(ENABLE_PRECOMMIT)
    setup_precommit()
endif()

find_package(KDBindings REQUIRED)
find_path(ARDUINOJSON_INCLUDE_DIRS "ArduinoJson.h")
include_directories(SYSTEM ${ARDUINOJSON_INCLUDE_DIRS})
find_package(SDL2 REQUIRED)
find_package(lvgl-ssd1322 REQUIRED)
find_package(lvgl-ssd1322-drivers REQUIRED)
find_package(SQLite3 REQUIRED)
if(ENABLE_BOOST)
    find_package(Boost CONFIG REQUIRED)
    add_definitions(-DWITH_BOOST)
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
