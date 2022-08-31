add_definitions(-DLV_CONF_INCLUDE_SIMPLE=1 -DLV_LVGL_H_INCLUDE_SIMPLE)

add_executable(laptimer src/lv_conf.h)

target_sources(laptimer
PRIVATE
    ${LVGL_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/laptimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_conf.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_drv_conf.h
)

TARGET_INCLUDE_DIRECTORIES(laptimer
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

TARGET_LINK_LIBRARIES(laptimer
PRIVATE
    ${SDL2_LIBRARIES}
)


