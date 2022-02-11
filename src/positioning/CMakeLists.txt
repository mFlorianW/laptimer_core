add_library(Positioning INTERFACE)
add_library(LaptimerCore::Positioning ALIAS Positioning)

target_include_directories(Positioning
    INTERFACE
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Positioning INTERFACE
INTERFACE
    KDAB::KDBindings
)