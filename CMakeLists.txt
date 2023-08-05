cmake_minimum_required(VERSION 3.24)

# Set C++ compiler flags before `project`
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_NAME "Dusk-Engine")
project(${PROJECT_NAME} LANGUAGES C CXX)

# Include cmake scripts
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPM.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake")

list(APPEND DUSK_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

list(APPEND DUSK_LIBRARIES
    EnTT
    fmt::fmt
    glad_gl_core_45
    glfw
    glm::glm
    imgui
    nlohmann_json::nlohmann_json
    OpenMP::OpenMP_CXX
    spdlog
    stb
    tinyobjloader
)

set(DUSK "dusk")
add_subdirectory("src")
