CPMAddPackage("gh:skypjack/entt@3.12.2")

CPMAddPackage("gh:fmtlib/fmt#9.1.0")

CPMAddPackage(
    NAME glad
    VERSION 2.0.4
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    DOWNLOAD_ONLY YES
)

if (glad_ADDED)
    add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
    glad_add_library(glad_gl_core_45 REPRODUCIBLE API gl:core=4.5)
endif()

CPMAddPackage(
    NAME GLFW
    GITHUB_REPOSITORY glfw/glfw
    GIT_TAG 3.3.8
    OPTIONS
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BULID_DOCS OFF"
)

CPMAddPackage("gh:g-truc/glm#0.9.9.8")

CPMAddPackage("gh:ocornut/imgui#docking")

if (imgui_ADDED)
    aux_source_directory("${imgui_SOURCE_DIR}" imgui_SOURCE_FILES)
    list(APPEND imgui_SOURCE_FILES
        "${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
        "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
    )
    add_library(imgui STATIC ${imgui_SOURCE_FILES})
    target_include_directories(imgui PRIVATE "${imgui_SOURCE_DIR}")
    target_link_libraries(imgui PRIVATE glad_gl_core_45)
endif()

CPMAddPackage(
    NAME nlohmann_json
    VERSION 3.11.2
    GITHUB_REPOSITORY nlohmann/json
    OPTIONS
        "JSON_BuildTests OFF"
)

CPMAddPackage("gh:gabime/spdlog@1.11.0")

CPMAddPackage(
    NAME stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    DOWNLOAD_ONLY YES
)

if (stb_ADDED)
    add_library(stb INTERFACE)
    target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})
endif()

CPMAddPackage("gh:tinyobjloader/tinyobjloader#v2.0.0rc10")

find_package(OpenMP REQUIRED)
