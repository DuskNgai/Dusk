# Configure all the files in the directory.
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" SOURCE_FILES)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/camera" SOURCE_FILES)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/opengl" SOURCE_FILES)

# Get the name of the folder where the `CMakeLists.txt` currently locates.
get_filename_component(FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)
# Build up a library.
add_library(dusk_${FOLDER_NAME} STATIC ${SOURCE_FILES})
target_include_directories(dusk_${FOLDER_NAME} PRIVATE ${DUSK_INCLUDES})
target_link_libraries(dusk_${FOLDER_NAME} PRIVATE ${DUSK_LIBRARIES})
