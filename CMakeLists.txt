cmake_minimum_required(VERSION 3.15)
project(WolfEngine VERSION 0.1.0)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

# Disable Assimp extras
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)

# Add subdirectories
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/assimp)
add_subdirectory(thirdparty/glew/build/cmake)

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

target_include_directories(Wolf PUBLIC
    ${CMAKE_SOURCE_DIR}/thirdparty/glfw/include 
    ${CMAKE_SOURCE_DIR}/thirdparty/glm 
    ${CMAKE_SOURCE_DIR}/thirdparty/glew/include 
    ${CMAKE_SOURCE_DIR}/thirdparty/assimp/include 
    ${OPENGL_INCLUDE_DIRS}
)

target_link_libraries(Wolf PUBLIC
    assimp
    glfw
    glew
    ${OPENGL_LIBRARIES}
)
