add_library(Positioning INTERFACE)
add_library(LaptimerCore::Positioning ALIAS Positioning)

target_include_directories(Positioning
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Positioning INTERFACE
INTERFACE
    KDAB::KDBindings
)