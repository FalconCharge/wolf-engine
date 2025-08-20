    cmake_minimum_required(VERSION 3.15)
    project(WolfProjectRoot)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Set global output directories for all targets
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

    # Keep config-specific folders (bin/Debug, bin/Release, etc.)
    foreach(OUTPUTCONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib/${OUTPUTCONFIG})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib/${OUTPUTCONFIG})
    endforeach()

    # Add subprojects
    add_subdirectory(src)       # Game.exe
    add_subdirectory(WolfEditor)        # WolfEngine
    add_subdirectory(game) # WolfEditor.exe

    # Compile defs
    target_compile_definitions(WolfEngine PRIVATE GLM_ENABLE_EXPERIMENTAL)
    target_compile_definitions(WolfEditor PRIVATE GLM_ENABLE_EXPERIMENTAL)
