#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../gll_util/gll_util.h"
#include "../gll_util/gll_camera.h"
#include <glm/glm.hpp>

 
void processInput(GLFWwindow *window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

gll::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float xprev = SCR_WIDTH / 2;
float yprev = SCR_HEIGHT / 2;

float delta_time = 0;
float prev_time = 0;
float fov = 45.0f;

int main(int argc, char* argv[])
{
    gll::initGLFW();
    GLFWwindow* window = gll::createGLFWwindow(SCR_WIDTH, SCR_HEIGHT);
    if (window == nullptr) {
        return -1;
    }
    if(!gll::initGLAD())
        return -2;
    
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, gll::frameBufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    gll::Shader light_shader;
    light_shader.load("../textures/09.2.texture.vs", "../textures/09.2.texture.fs");
    gll::Shader cube_shader;
    cube_shader.load("../textures/09.1.texture.vs", "../textures/09.1.texture.fs");

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    gll::VAVBEBO light_vavbo;
    light_vavbo.bind(vertices, sizeof(vertices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    gll::VAVBEBO cube_vavbo;
    cube_vavbo.bind(vertices, sizeof(vertices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glm::vec3 light_pos(0.2f, 0.0f, 2.0f);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float curr_time = glfwGetTime();
        delta_time = curr_time - prev_time;
        prev_time = curr_time;
        processInput(window);

        // render
        gll::render();
        glClear(GL_DEPTH_BUFFER_BIT);
        
        // render container
        cube_shader.use();
        cube_shader.setVec3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        cube_shader.setVec3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        cube_shader.setVec3f("light_pos", light_pos);
        cube_shader.setVec3f("view_pos", camera.getPosition());

        glm::mat4 model(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        cube_shader.setMat4f("projection", projection);
        cube_shader.setMat4f("view", view);
        cube_shader.setMat4f("model", model);

        cube_vavbo.bindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        light_shader.use();
        light_shader.setMat4f("projection", projection);
        light_shader.setMat4f("view", view);
        model = glm::translate(model, light_pos);
        model = glm::scale(model, glm::vec3(0.2));
        light_shader.setMat4f("model", model);
        
        light_vavbo.bindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    light_vavbo.release();
    cube_vavbo.release();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(gll::Camera::MOVE_FORWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(gll::Camera::MOVE_BACKWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(gll::Camera::MOVE_LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(gll::Camera::MOVE_RIGHT, delta_time);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    static bool is_first = true;
    if(is_first){
        xprev = xpos;
        yprev = ypos;
        is_first = false;
    }
    float xoffset = xpos - xprev;
    float yoffset = yprev - ypos;
    xprev = xpos;
    yprev = ypos;
    camera.processMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}