add_definitions(-DLV_CONF_INCLUDE_SIMPLE=1 -DLV_LVGL_H_INCLUDE_SIMPLE)

add_library(ssd1322Sehll STATIC)
add_library(LaptimerCore::Ssd1322Shell ALIAS ssd1322Sehll)

target_sources(ssd1322Sehll
    PRIVATE

    # Root
    ${LVGL_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/INavigationHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IOpenCloseHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreenModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreenModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuEntryList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuEntryList.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuScreenModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuScreenModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuScreen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuScreen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/NavigatableModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/NavigatableModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PopupRequest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PopupRequest.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Screen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Screen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ScreenModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IMenuEntry.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuEntry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuEntry.hpp

    # Command
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/CloseCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/CloseCommand.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/ICommand.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/NavigateDownCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/NavigateDownCommand.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/NavigateUpCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/NavigateUpCommand.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/OpenCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/OpenCommand.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/ShowMainScreenCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/ShowMainScreenCommand.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/ShowMenuScreenCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/ShowMenuScreenCommand.hpp

    # View
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/ActiveSessionView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/ActiveSessionView.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/ListView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/ListView.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/MainScreenView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/MainScreenView.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/MenuEntryView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/MenuEntryView.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/PopupView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/PopupView.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/View.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/View.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/SessionView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/SessionView.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/TableView.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/TableView.cpp

    # ViewModel
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/ActiveSessionModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/ActiveSessionModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/StatusBarModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/StatusBarModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/SessionViewModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/SessionViewModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/TableModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/TableModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/LapModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/LapModel.hpp

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ScreenModel.hpp
)

TARGET_INCLUDE_DIRECTORIES(ssd1322Sehll
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<INSTALL_INTERFACE:include/platform/desktop>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/platform/desktop>
    PRIVATE
    ${LVGL_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/dummy
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/include/platform/desktop
)

TARGET_LINK_LIBRARIES(ssd1322Sehll
    PUBLIC
    ${SDL2_LIBRARIES}
    LaptimerCore::Common
    LaptimerCore::Positioning
    LaptimerCore::Algorithm
    LaptimerCore::Session
    LaptimerCore::Workflow
    LaptimerCore::TrackManagement
    LaptimerCore::System
)
