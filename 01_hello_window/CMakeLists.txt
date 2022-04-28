cmake_minimum_required(VERSION 3.10)

project(hello_window)

add_executable(${PROJECT_NAME}
    main.cpp
    ${GLAD_PATH}/src/glad.c
    ${GL_UTIL_SRC}
)

# Add libraries
target_link_libraries(${PROJECT_NAME} 
    glfw
)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} 
        "-framework OpenGL")
endif()