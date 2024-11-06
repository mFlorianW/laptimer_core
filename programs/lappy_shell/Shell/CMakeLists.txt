qt_wrap_ui(UI
    MainWindow.ui
)

qt_add_qml_module(Shell
    URI "Lappy.Shell"
    OUTPUT_DIRECTORY "Lappy/Shell"
    IMPORT_PATH "Lappy/Shell"
    VERSION 1.0
    STATIC
    SOURCES
        ${UI}
        LappyShell.cpp
        LappyShell.cpp
)

add_library(LaptimerCore::LappyShell ALIAS Shell)
add_library(LaptimerCore::LappyShellPlugin ALIAS Shellplugin)

target_link_libraries(Shell
    PUBLIC
        Qt6::Widgets
        LaptimerCore::LappyShellSettings
        LaptimerCore::LappyShellSettingsPlugin
    PRIVATE
        LaptimerCore::DatabaseFile
        LaptimerCore::LappyShellCommon
        LaptimerCore::LappyShellApplications
        LaptimerCore::LappyShellApplicationsPlugin
)

target_include_directories(Shell
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
