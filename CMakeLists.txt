cmake_minimum_required(VERSION 3.10)

project(learn_OpenGL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "RELEASE")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_BINARY_DIR}/app)

# Include GLFW
find_package(glfw3 REQUIRED)

# Include neccessary path
set(PATH_3RDPARTY "${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/")

set(GLAD_PATH ${PATH_3RDPARTY}glad/ CACHE INTERNAL "GLAD path")

set(INC_PATH ${GLAD_PATH}include/ CACHE INTERNAL "include path")
list(APPEND INC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/gl_util/")
list(APPEND INC_PATH ${PATH_3RDPARTY}stb_image/)
list(APPEND INC_PATH ${PATH_3RDPARTY}glm/)
# message("Include path: ${INC_PATH}")

include_directories(
    ${INC_PATH}
)

# The GL utility sources
file(GLOB GL_UTIL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/gl_util/*.cpp)

# The switch to control the compilation
option(BUILD_CHAPTER_ALL "build all the project" ON)
option(BUILD_CHAPTER1 "build chapter #1" OFF)
option(BUILD_CHAPTER2 "build chapter #2" ON)

# Chapter #1: Foundamental knowledge
if(BUILD_CHAPTER_ALL OR BUILD_CHAPTER1)
    message("Build targets in Chapter #1")
    add_subdirectory(1_01_hello_window)
    add_subdirectory(1_02_hello_triangle)
    add_subdirectory(1_03_learn_shader)
    add_subdirectory(1_04_learn_texture)
    add_subdirectory(1_05_learn_glm)
    add_subdirectory(1_06_learn_coordinate)
    add_subdirectory(1_07_learn_camera)
endif()

# Chapter #2: Lightness
if(BUILD_CHAPTER_ALL OR BUILD_CHAPTER2)
    message("Build targets in Chapter #2")
    add_subdirectory(2_01_learn_color)
    add_subdirectory(2_02_learn_lighting)
endif()
message("${BUILD_CHAPTER_ALL} - ${BUILD_CHAPTER1} - ${BUILD_CHAPTER2}")
# # My Test
# add_subdirectory(test_ar)
# add_subdirectory(test_obj)