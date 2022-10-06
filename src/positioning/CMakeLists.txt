add_library(Positioning STATIC)
add_library(LaptimerCore::Positioning ALIAS Positioning)

target_sources(Positioning
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UTM.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ConstantVelocityPositionDateTimeProvider.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/IGPSInformationProvider.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/StaticGpsInformationProvider.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/IPositionInformationProvider.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/StaticPositionInformationProvider.hpp
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
    LaptimerCore::Common
    KDAB::KDBindings
)
