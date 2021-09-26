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

    gll::Shader myshader;
    myshader.load("../textures/06.1.texture.vs", "../textures/06.1.texture.fs");
    
    unsigned char type = std::stoi(argv[1]);
    if(type == 3){
        glfwSetScrollCallback(window, scrollCallback);
        glfwSetCursorPosCallback(window, mouseCallback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
        
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    gll::VAVBEBO vavbebo;
    vavbebo.bind(vertices, sizeof(vertices));
         
    glEnable(GL_DEPTH_TEST);
    // ------------------------------------------------------------------------

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    // load and create a texture 
    // -------------------------
    unsigned int texture;
    if( !gll::create2DTexture("../resources/container.jpg", texture) ){
        return -2;
    }
    unsigned int texture2;
    if( !gll::create2DTexture("../resources/awesomeface.png", texture2, GL_RGBA)) {
        return -2;
    }
    //tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    myshader.use(); // don't forget to activate/use the shader before setting uniforms!
    myshader.setInt("texture1", 0);
    myshader.setInt("texture2", 1);

    
    glm::mat4 I4(1.0f), model, view, projection;
    projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.2f, 100.0f);  
    myshader.setMat4f("projection", projection);


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

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        // render container
        myshader.use();
        
        if(type >= 1){
            if(type == 1){
                float radius = 10.f;
                float posx = sin(glfwGetTime()) * radius;
                float posz = cos(glfwGetTime()) * radius;
                view = glm::lookAt(glm::vec3(posx, 0.0, posz), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
            }
            else if(type >= 2){
                view = camera.getViewMatrix();
                if(type == 3){
                    projection = glm::perspective(glm::radians(camera.zoom), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.2f, 100.0f);  
                    myshader.setMat4f("projection", projection);
                }
            }
            myshader.setMat4f("view", view);
            
            vavbebo.bindVertexArray();
            for(unsigned int i = 0; i < 10; i++)
            {
                model = glm::translate(I4, cubePositions[i]);
                float angle = 20.0f * i; 
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                myshader.setMat4f("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vavbebo.release();

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