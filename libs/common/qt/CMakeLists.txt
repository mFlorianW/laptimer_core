add_library(CommonObjectQt OBJECT)
add_library(LaptimerCore::CommonObjectQt ALIAS CommonObjectQt)

target_sources(CommonObjectQt
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/GlobalSettingsBackend.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GlobalSettingsBackend.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GlobalSettingsReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GlobalSettingsReader.hpp
)

target_link_libraries(CommonObjectQt
PUBLIC
    Qt6::Core
)

target_include_directories(CommonObjectQt
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_library(CommonQt STATIC)
add_library(LaptimerCore::CommonQt ALIAS CommonQt)

target_link_libraries(CommonQt
PUBLIC
    LaptimerCore::CommonObjectQt
)
