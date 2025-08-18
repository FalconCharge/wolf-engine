# Collect all .cpp files in game/src
file(GLOB_RECURSE GAME_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Sanity check: make sure we actually found something
if (NOT GAME_FILES)
    message(FATAL_ERROR "No source files found for Game in ${CMAKE_CURRENT_SOURCE_DIR}/src")
endif()

# Create the executable
add_executable(Game ${GAME_FILES})

# Includes
target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/wolf
)

# Link engine
target_link_libraries(Game PRIVATE WolfEngine)

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

