cmake_minimum_required(VERSION 3.10)

project(learn_OpenGL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "RELEASE")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_CURRENT_SOURCE_DIR}/build/app)

# Include GLFW
find_package(glfw3 REQUIRED)

# Include neccessary path
set(PATH_3RDPARTY "${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/")

set(GLAD_PATH ${PATH_3RDPARTY}glad/ CACHE INTERNAL "GLAD path")

set(INC_PATH ${GLAD_PATH}include/ CACHE INTERNAL "include path")
list(APPEND INC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/gl_util/")
list(APPEND INC_PATH ${PATH_3RDPARTY}stb_image/)
list(APPEND INC_PATH ${PATH_3RDPARTY}glm/)
message("Include path: ${INC_PATH}")

include_directories(
    ${INC_PATH}
)


add_subdirectory(01_hello_window)
add_subdirectory(02_hello_triangle)
add_subdirectory(03_learn_shader)
add_subdirectory(04_learn_texture)
add_subdirectory(05_learn_glm)
