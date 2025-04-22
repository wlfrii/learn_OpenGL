cmake_minimum_required(VERSION 3.10)

project(hello_window)

add_executable(${PROJECT_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE gl_util)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} 
        "-framework OpenGL")
endif()