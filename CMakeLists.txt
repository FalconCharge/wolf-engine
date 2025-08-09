cmake_minimum_required(VERSION 3.15)
project(WolfProjectRoot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Wolf engine library
add_subdirectory(src)       # src/CMakeLists.txt builds the WolfEngine library

# Add editor executable
add_subdirectory(WolfEditor)  # WolfEditor/CMakeLists.txt builds the editor

# IDK whats really happening here
target_compile_definitions(WolfEngine PRIVATE GLM_ENABLE_EXPERIMENTAL)
target_compile_definitions(WolfEditor PRIVATE GLM_ENABLE_EXPERIMENTAL)
