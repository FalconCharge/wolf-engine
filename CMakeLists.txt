cmake_minimum_required(VERSION 3.15)
project(WolfEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies from vcpkg
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

# Collect ALL source files (including your main.cpp)
file(GLOB_RECURSE SAMPLEFW_SOURCE_FILES ${CMAKE_SOURCE_DIR}/samplefw/*.cpp)
file(GLOB_RECURSE WOLF_SOURCE_FILES ${CMAKE_SOURCE_DIR}/wolf/*.cpp)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Create the executable with all sources
add_executable(WolfEngine
    ${SAMPLEFW_SOURCE_FILES}
    ${WOLF_SOURCE_FILES}
    ${SOURCE_FILES}
)

# Link dependencies
target_link_libraries(WolfEngine PRIVATE
    glfw
    GLEW::GLEW
    OpenGL::GL
    assimp::assimp
    glm::glm
)

# Had to add this to avoid GLM issues with C++17
target_compile_definitions(WolfEngine PRIVATE GLM_ENABLE_EXPERIMENTAL)