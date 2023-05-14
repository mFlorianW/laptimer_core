find_package(Qt5 REQUIRED COMPONENTS Core Quick Gui Network Widgets)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

add_library(lappy_sessiondl_obj STATIC)
add_library(LaptimerCore::SessionDlObj ALIAS lappy_sessiondl_obj)

target_sources(lappy_sessiondl_obj
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/LappySessionDownloader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CliOptions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindowModel.cpp

PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CliOptions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindowModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LappySessionDownloader.hpp
)

target_link_libraries(lappy_sessiondl_obj
PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
    Qt5::Network
    Qt5::Widgets
    LaptimerCore::RestQt
    LaptimerCore::Workflow
    LaptimerCore::Storage
    LaptimerCore::LibraryPath
)

target_include_directories(lappy_sessiondl_obj
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_executable(lappy_sessiondl)

qt5_add_resources(RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc
)

target_sources(lappy_sessiondl
PRIVATE
    ${RESOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lappy_sessiondl.cpp
)

target_link_libraries(lappy_sessiondl
PRIVATE
    LaptimerCore::SessionDlObj
)
