add_definitions(-DLV_CONF_INCLUDE_SIMPLE=1 -DLV_LVGL_H_INCLUDE_SIMPLE)

add_executable(laptimer)

target_sources(laptimer
PRIVATE
    # Root
    ${LVGL_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/laptimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_conf.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_drv_conf.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/INavigationHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IOpenCloseHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreenModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreenModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuEntryModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuEntryModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuScreen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuScreen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/NavigatableModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/NavigatableModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PopupRequest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PopupRequest.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Screen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Screen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ScreenModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ScreenModel.hpp

    # Platform
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/desktop/Controls.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/desktop/Controls.hpp

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

    # View/Dummy
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/dummy/DummyListView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/dummy/DummyListView.hpp

    # ViewModel
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/ActiveSessionModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/ActiveSessionModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/StatusBarModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/StatusBarModel.hpp
)

TARGET_INCLUDE_DIRECTORIES(laptimer
PRIVATE
    ${LVGL_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/dummy
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/desktop
)

TARGET_LINK_LIBRARIES(laptimer
PRIVATE
    ${SDL2_LIBRARIES}
    LaptimerCore::Common
    LaptimerCore::Positioning
    LaptimerCore::Algorithm
    LaptimerCore::Session
    LaptimerCore::Workflow
)


