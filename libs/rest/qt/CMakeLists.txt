find_package(Qt5 REQUIRED COMPONENTS Core Network)

add_library(RestQt SHARED)
add_library(LaptimerCore::RestQt ALIAS RestQt)

target_sources(RestQt
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/QRestClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QRestClient.hpp
)

target_link_libraries(RestQt
PUBLIC
    LaptimerCore::Rest
PRIVATE
    Qt5::Core
    Qt5::Network
)

target_include_directories(RestQt
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_definitions(RestQt PRIVATE QT_NO_KEYWORDS)
