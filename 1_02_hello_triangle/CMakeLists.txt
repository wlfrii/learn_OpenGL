cmake_minimum_required(VERSION 3.10)

project(hello_triangle)

add_executable(${PROJECT_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE gl_util)

