aux_source_directory("." DUSK_SOURCE_FILES)
aux_source_directory("core/application" DUSK_SOURCE_FILES)
aux_source_directory("core/event" DUSK_SOURCE_FILES)
aux_source_directory("core/window" DUSK_SOURCE_FILES)
aux_source_directory("renderer" DUSK_SOURCE_FILES)
aux_source_directory("renderer/opengl" DUSK_SOURCE_FILES)
aux_source_directory("scene/camera" DUSK_SOURCE_FILES)
aux_source_directory("utils" DUSK_SOURCE_FILES)

# The dynamic library
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_library(${DUSK} SHARED ${DUSK_SOURCE_FILES})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_library(${DUSK} STATIC ${DUSK_SOURCE_FILES})
else()
    message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} is currently not supported!")
endif()

target_include_directories(${DUSK} PUBLIC ${DUSK_INCLUDES})
target_link_libraries(${DUSK} PUBLIC ${DUSK_LIBRARIES})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result)

    if(result)
        set_target_properties(${DUSK} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
endif()
