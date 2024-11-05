qt_add_qml_module(Applications
    URI "Lappy.Shell.Applications"
    OUTPUT_DIRECTORY "Lappy/Shell/Applications"
    IMPORT_PATH "Lappy/Shell/Applications"
    VERSION 1.0
    STATIC
    QML_FILES
        qml/ApplicationOverview.qml
        qml/controls/ApplicationButton.qml
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationConfig.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationConfig.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationConfigReader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationConfigReader.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationFinder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationFinder.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationListModel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationListModel.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationModel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationModel.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationOverviewWidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationOverviewWidget.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ProcessManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ProcessManager.hpp
)

add_library(LaptimerCore::LappyShellApplications ALIAS Applications)
add_library(LaptimerCore::LappyShellApplicationsPlugin ALIAS Applicationsplugin)

target_include_directories(Applications
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(Applications
    PUBLIC
        LaptimerCore::LappyShellCommon
        Qt6::QuickWidgets
)
