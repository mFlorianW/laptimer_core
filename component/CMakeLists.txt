FetchContent_Declare(
    KDBindings
    GIT_REPOSITORY https://github.com/KDAB/KDBindings.git
    GIT_TAG        37a49b3eaa64861464da8bc506dccecf7516101f
)
FetchContent_MakeAvailable(KDBindings)
list(APPEND CMAKE_MODULE_PATH ${kdbindings_BUILD_DIR})

file(GLOB SRC_FILES_ALGORITHM
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/alogrithm/src/*.cpp
)

file(GLOB SRC_FILES_COMMON
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/common/src/*.cpp
)

idf_component_register(
SRCS
    "${SRC_FILES_ALGORITHM}"
INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE}/../src/alogrithm/include"
    "${CMAKE_CURRENT_SOURCE}/../src/common/include"
    "${CMAKE_CURRENT_SOURCE}/../src/positioning/include"
)