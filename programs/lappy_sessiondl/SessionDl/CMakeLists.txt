qt_add_qml_module(SessionDl
    URI "Lappy.SessionDownloader"
    OUTPUT_DIRECTORY "Lappy/SessionDownloader"
    IMPORT_PATH "Lappy/SessionDownloader"
    VERSION 1.0
    STATIC
    QML_FILES
        qml/MainWindow.qml
    SOURCES
        CliOptions.cpp
        CliOptions.hpp
        MainWindowModel.cpp
        MainWindowModel.hpp
        SessionDownloader.cpp
        SessionDownloader.hpp
)

add_library(LaptimerCore::LappySessionDl ALIAS SessionDl)
add_library(LaptimerCore::LappySessionDlPlugin ALIAS SessionDlplugin)

target_link_libraries(SessionDl
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        Qt6::Network
        Qt6::Widgets
        LaptimerCore::RestQt
        LaptimerCore::SystemQt
        LaptimerCore::Workflow
        LaptimerCore::Storage
        LaptimerCore::LibraryPath
)

target_include_directories(SessionDl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
