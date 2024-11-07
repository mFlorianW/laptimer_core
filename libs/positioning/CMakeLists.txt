add_library(Positioning STATIC)
add_library(LaptimerCore::Positioning ALIAS Positioning)

target_sources(Positioning
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UTM.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ConstantVelocityPositionDateTimeProvider.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/IGPSInformationProvider.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/StaticGpsInformationProvider.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/StaticPositionDateTimeProvider.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ConstantVelocityPositionDateTimeProvider.hpp
)

target_include_directories(Positioning
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Positioning
PUBLIC
    Rapid::Common
    LaptimerCore::System
    KDAB::KDBindings
)

if(ENABLE_QT)
    add_library(PositioningQt STATIC)
    add_library(LaptimerCore::PositioningQt ALIAS PositioningQt)

    target_sources(PositioningQt
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/qt/CsvGpsFileReader.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/qt/CsvGpsFileReader.hpp
    )

    target_include_directories(PositioningQt
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/qt>
    )

    target_link_libraries(PositioningQt
    PUBLIC
        LaptimerCore::Positioning
        Qt6::Core
    )
endif()
