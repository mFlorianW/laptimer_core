set(_THIS_MODULE_BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")

macro(fetch_lvgl)
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
    )

    file(GLOB_RECURSE LVGL_SOURCES_DISPLAY
        "${lvgldrivers_SOURCE_DIR}/display/*.c"
        "${lvgldrivers_SOURCE_DIR}/indev/*.c"
    )

    add_library(lvgl-ssd1322 STATIC ${LVGL_SOURCES})
    add_library(lvgl-ssd1322::lvgl-ssd1322 ALIAS lvgl-ssd1322)
    target_include_directories(lvgl-ssd1322
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/configuration/cmake/lvgl/include>
    )
    target_compile_definitions(lvgl-ssd1322 PUBLIC -DLV_CONF_INCLUDE_SIMPLE=1 -DLV_LVGL_H_INCLUDE_SIMPLE)


    add_library(lvgl-ssd1322-drivers STATIC ${LVGL_SOURCES_DISPLAY})
    add_library(lvgl-ssd1322-drivers::lvgl-ssd1322-drivers ALIAS lvgl-ssd1322-drivers)
    target_include_directories(lvgl-ssd1322-drivers
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/configuration/cmake/lvgl/include>
    )
    target_compile_definitions(lvgl-ssd1322-drivers PUBLIC -DLV_CONF_INCLUDE_SIMPLE=1 -DLV_LVGL_H_INCLUDE_SIMPLE)
endmacro()
