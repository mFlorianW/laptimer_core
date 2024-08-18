macro(fetch_kdbindings)
    FetchContent_Declare(
        KDBindings
        GIT_REPOSITORY https://github.com/KDAB/KDBindings.git
        GIT_TAG        37a49b3eaa64861464da8bc506dccecf7516101f
    )
    FetchContent_MakeAvailable(KDBindings)
    list(APPEND CMAKE_PREFIX_PATH ${kdbindings_BINARY_DIR})
endmacro()
