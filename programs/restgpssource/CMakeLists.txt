find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Quick Location)

add_executable(restgpssource)

qt5_add_resources(RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc
)
list(APPEND QML_IMPORT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/qml)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

target_sources(restgpssource
PRIVATE
    ${RESOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/restgpssource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RestGpsSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RestGpsSource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowViewModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowViewModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PositionListModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PositionListModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RestHttpClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RestHttpClient.hpp
)

target_link_libraries(restgpssource
PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Quick
    Qt5::Location
    LaptimerCore::Common
    LaptimerCore::Positioning
    LaptimerCore::PositioningQt
)
