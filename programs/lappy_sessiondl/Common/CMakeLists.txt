add_library(SessionDlCommonObject OBJECT)
add_library(LaptimerCore::SessionDlCommonObject ALIAS SessionDlCommonObject)

target_sources(SessionDlCommonObject
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/LoggingCategories.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LoggingCategories.hpp
)

target_link_libraries(SessionDlCommonObject
PUBLIC
    Qt6::Core
)

target_include_directories(SessionDlCommonObject
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_library(SessionDlCommon STATIC)
add_library(LaptimerCore::SessionDlCommon ALIAS SessionDlCommon)

target_link_libraries(SessionDlCommon
PUBLIC
    LaptimerCore::SessionDlCommonObject
)
