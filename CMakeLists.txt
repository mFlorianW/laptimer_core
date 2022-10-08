cmake_minimum_required(VERSION 3.5)

project(LaptimerCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)
include(FeatureSummary)

option(ENABLE_TEST "Enable unit tests" OFF)
option(ENABLE_CATCH2_FETCH "This option enables that catch2 is fetched in configuration" OFF)
option(ENABLE_KDBINDINGS_FETCH "This option enables that KDBindings is fetched in configuration" ON)
option(ENABLE_ARDUINOJSON_FETCH "This option enables that ARDUIONJSON is fetched in configuration" ON)
option(ENABLE_LVGL_FETCH "This option enables that LVGL is fetched in configuration" ON)

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

if (ENABLE_LVGL_FETCH)
    FetchContent_Declare(
        Lvgl
        GIT_REPOSITORY https://github.com/lvgl/lvgl.git
        GIT_TAG c5bacff2faff0df248410aec6ba53f39582af13d
    )
    FetchContent_MakeAvailable(Lvgl)

    FetchContent_Declare(
            LvglDrivers
            GIT_REPOSITORY https://github.com/lvgl/lv_drivers.git
            GIT_TAG 8de9b6749c0c86c998ac6ca50797f0a54744d360
    )
    FetchContent_MakeAvailable(LvglDrivers)

    include_directories(SYSTEM
        "${lvgl_SOURCE_DIR}"
        "${lvgl_SOURCE_DIR}/src"
        "${lvgl_SOURCE_DIR}/src/lv_core/"
        "${lvgl_SOURCE_DIR}/src/lv_draw"
        "${lvgl_SOURCE_DIR}/src/lv_font"
        "${lvgl_SOURCE_DIR}/src/lv_gpu"
        "${lvgl_SOURCE_DIR}/src/lv_hal"
        "${lvgl_SOURCE_DIR}/src/lv_misc"
        "${lvgl_SOURCE_DIR}/src/lv_themes"
        "${lvgl_SOURCE_DIR}/src/lv_widgets"
        "${lvgldrivers_SOURCE_DIR}/display"
        "${lvgldrivers_SOURCE_DIR}/indev"
    )

    file(GLOB_RECURSE LVGL_SOURCES
        "${lvgl_SOURCE_DIR}/src/lv_core/*.c"
        "${lvgl_SOURCE_DIR}/src/lv_draw/*.c"
        "${lvgl_SOURCE_DIR}/src/lv_font/*.c"
        "${lvgl_SOURCE_DIR}/src/lv_gpu/*.c"
        "${lvgl_SOURCE_DIR}/src/lv_hal/*.c"
        "${lvgl_SOURCE_DIR}/src/lv_misc/*.c"
        "${lvgl_SOURCE_DIR}/src/lv_themes/*.c"
        "${lvgl_SOURCE_DIR}/src/lv_widgets/*.c"
        "${lvgldrivers_SOURCE_DIR}/display/*.c"
        "${lvgldrivers_SOURCE_DIR}/indev/*.c"
    )

    find_package(SDL2 REQUIRED)
endif(ENABLE_LVGL_FETCH)

add_subdirectory(src)
add_subdirectory(testprograms)

if(ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif(ENABLE_TEST)

feature_summary(WHAT ALL)
