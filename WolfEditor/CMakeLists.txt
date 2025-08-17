
file(GLOB EDITOR_SOURCES
    "editor/*.cpp"
    "editor/windows/*.cpp"
)


add_executable(WolfEditor ${EDITOR_SOURCES})

# Include engine headers and external dependencies
target_include_directories(WolfEditor PRIVATE
    ${CMAKE_SOURCE_DIR}/wolf
    ${CMAKE_SOURCE_DIR}/external
)

# Find and link imgui and other libs from vcpkg
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(WolfEditor PRIVATE
    WolfEngine        # link the engine lib
    imgui::imgui      
    glfw
    GLEW::GLEW
    OpenGL::GL
)
