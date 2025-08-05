cmake_minimum_required(VERSION 3.15)
project(WolfEngine VERSION 0.1.0)

# OpenGL & vcpkg dependencies
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

# Collect source files
file(GLOB_RECURSE SAMPLEFW_SOURCE_FILES ${CMAKE_SOURCE_DIR}/samplefw/*.cpp)
file(GLOB_RECURSE SAMPLEFW_HEADER_FILES ${CMAKE_SOURCE_DIR}/samplefw/*.hpp)
file(GLOB_RECURSE WOLF_SOURCE_FILES ${CMAKE_SOURCE_DIR}/wolf/*.cpp)
file(GLOB_RECURSE WOLF_HEADER_FILES ${CMAKE_SOURCE_DIR}/wolf/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.hpp)

add_library(Wolf STATIC
    ${SAMPLEFW_SOURCE_FILES}
    ${SAMPLEFW_HEADER_FILES}
    ${WOLF_SOURCE_FILES}
    ${WOLF_HEADER_FILES}
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_link_libraries(Wolf PUBLIC
    glfw
    GLEW::GLEW
    OpenGL::GL
    assimp::assimp
    glm::glm
)
