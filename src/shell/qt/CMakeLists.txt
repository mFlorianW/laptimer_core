find_package(Qt5 REQUIRED COMPONENTS Core Quick Location)

qt5_add_resources(RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc
)
list(APPEND QML_IMPORT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/qml)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

add_library(QtShell SHARED)
add_library(LaptimerCore::QtShell ALIAS QtShell)

target_sources(QtShell
PRIVATE
    ${RESOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QtShell.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowViewModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowViewModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LaptimeModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LaptimeModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils.hpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QtShell.hpp
)

target_include_directories(QtShell
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(QtShell
PUBLIC
    LaptimerCore::Common
    LaptimerCore::Positioning
    LaptimerCore::PositioningQt
    LaptimerCore::Algorithm
    Qt5::Core
    Qt5::Quick
    Qt5::Location
)
