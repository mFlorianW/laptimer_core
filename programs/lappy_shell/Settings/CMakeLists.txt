qt_add_qml_module(Settings
    URI "Lappy.Settings"
    OUTPUT_DIRECTORY "Lappy/Settings"
    IMPORT_PATH "Lappy/Settings"
    VERSION 1.0
    STATIC
    SOURCES
        GlobalSettingsWriter.cpp
        GlobalSettingsWriter.hpp
)

add_library(LaptimerCore::LappyShellSettings ALIAS Settings)
add_library(LaptimerCore::LappyShellSettingsPlugin ALIAS Settingsplugin)

target_link_libraries(Settings
    PUBLIC
        Qt6::Quick
    PRIVATE
        LaptimerCore::DatabaseFile
        LaptimerCore::LappyShellCommon
)

target_include_directories(Settings
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
