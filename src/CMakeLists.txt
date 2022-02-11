if(ENABLE_KDBINDINGS_FETCH)
    FetchContent_Declare(
        KDBindings
        GIT_REPOSITORY https://github.com/KDAB/KDBindings.git
        GIT_TAG        37a49b3eaa64861464da8bc506dccecf7516101f
    )
    FetchContent_MakeAvailable(KDBindings)
    list(APPEND CMAKE_MODULE_PATH ${kdbindings_BUILD_DIR})
else()
find_package(KDBindings CONFIG REQUIRED)
endif()

add_subdirectory(algorithm)
add_subdirectory(common)
add_subdirectory(positioning)