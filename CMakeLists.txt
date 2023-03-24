cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "Dusk-Engine")
project(${PROJECT_NAME} LANGUAGES C CXX)

# Dependencies and third libraries
add_subdirectory("dependency/fmt")
add_subdirectory("dependency/glfw")
add_subdirectory("dependency/glm")
add_subdirectory("dependency/nlohmann")
add_subdirectory("dependency/spdlog")

list(APPEND DUSK_GUI_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/glad/src/glad.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/imgui/imgui.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/imgui/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/imgui/imgui_tables.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/imgui/imgui_widgets.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/imgui/backends/imgui_impl_opengl3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/stb/stb_image.cpp"
)

list(APPEND DUSK_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/fmt/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/glad/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/glfw/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/imgui/backends"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/nlohmann/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/spdlog/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependency/stb"
)

list(APPEND DUSK_LIBRARIES
    fmt::fmt
    glfw
    glm::glm
)

find_package(OpenMP REQUIRED)
if (OpenMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_subdirectory("src")
aux_source_directory(src DUSK_SOURCE_FILES)

# The dynamic library
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_library(dusk SHARED ${DUSK_SOURCE_FILES} ${DUSK_GUI_SOURCES})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_library(dusk STATIC ${DUSK_SOURCE_FILES} ${DUSK_GUI_SOURCES})
else()
    message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} is currently not supported!")
endif()

target_include_directories(dusk PUBLIC ${DUSK_INCLUDES})
target_link_libraries(dusk PUBLIC
    ${DUSK_LIBRARIES}
    dusk_core
    dusk_renderer
)
