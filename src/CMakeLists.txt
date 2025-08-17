# Gather all cpp files recursively in src/
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/**/*.cpp"
)



add_library(WolfEngine STATIC ${SRC_FILES})

# Include public headers from wolf/
target_include_directories(WolfEngine PUBLIC
    ${CMAKE_SOURCE_DIR}/wolf
    ${CMAKE_SOURCE_DIR}/external
)

# Link dependencies from vcpkg
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

target_link_libraries(WolfEngine PUBLIC
    glfw
    GLEW::GLEW
    OpenGL::GL
    assimp::assimp
    glm::glm
)

# Optional: enable any compile definitions, e.g.
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
