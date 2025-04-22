cmake_minimum_required(VERSION 3.10)

project(learn_OpenGL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "RELEASE")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_BINARY_DIR}/app)

# The GL utility sources
add_subdirectory(gl_util)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_util/include
)

# The switch to control the compilation
option(BUILD_CHAPTER_ALL "build all the project" ON)

# Chapter #1: Foundamental knowledge
option(BUILD_CHAPTER1 "build chapter #1" ON)
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
option(BUILD_CHAPTER2 "build chapter #2" ON)
if(BUILD_CHAPTER_ALL OR BUILD_CHAPTER2)
    message("Build targets in Chapter #2")
    add_subdirectory(2_01_learn_color)
    add_subdirectory(2_02_learn_lighting)
endif()

# My practices
option(BUILD_PRACTICE "build practices" ON)
if(BUILD_CHAPTER_ALL OR BUILD_PRACTICE)
    # add_subdirectory(test_AR)
    # add_subdirectory(test_model)
    # add_subdirectory(test_points3D)
endif()