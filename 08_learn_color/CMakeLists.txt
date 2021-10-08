cmake_minimum_required(VERSION 3.10)

project(learn_color)

add_executable(${PROJECT_NAME}
    main.cpp
    ${GLAD_PATH}/src/glad.c
)


# Add libraries
target_link_libraries(${PROJECT_NAME} 
    glfw
)