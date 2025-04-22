cmake_minimum_required(VERSION 3.10)

project(learn_camera)

add_executable(${PROJECT_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE gl_util)