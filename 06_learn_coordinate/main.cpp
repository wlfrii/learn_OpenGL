#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../gll_util/gll_util.h"
#include <glm/glm.hpp>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


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
    
    gll::VAVBEBO vavbebo;
    unsigned char type = 0;
    if(argc >= 2){
        type = std::stoi(argv[1]);
        if(type == 1){
            float vertices[] = {
                // positions         // texture coords
                0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
                0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
                -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
            };
            unsigned int indices[] = {  
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
            };   
            vavbebo.bind(vertices, sizeof(vertices), indices, sizeof(indices));
        }
        else if(type >= 2){
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
            vavbebo.bind(vertices, sizeof(vertices));

            if(type >= 3){
                // glEnable() and glDisable() allows we enable or disable a function
                glEnable(GL_DEPTH_TEST);
            }
        }  
    }
    else{
        printf("Please set an input arguments range in [1,2]\n");
        return 0;
    }

    // ------------------------------------------------------------------------

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    if( !gll::create2DTexture("../resources/container.jpg", texture) ){
        return -2;
    }
    unsigned int texture2;
    if( !gll::create2DTexture("../resources/awesomeface.png", texture2)) {
        return -2;
    }
    //tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    myshader.use(); // don't forget to activate/use the shader before setting uniforms!
    myshader.setInt("texture1", 0);
    myshader.setInt("texture2", 1);

    
    glm::mat4 I4(1.0f), model, view, projection;
    if(type == 1){
        model = glm::rotate(I4, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
        view = glm::translate(I4, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.2f, 100.0f);
        myshader.setMat4f("model", model);
        myshader.setMat4f("view", view);
        myshader.setMat4f("projection", projection);
    }

    view = glm::translate(I4, glm::vec3(0.0f, 0.0f, -3.0f));
    myshader.setMat4f("view", view);

    projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.2f, 100.0f);  
    myshader.setMat4f("projection", projection);
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        gll::processInput(window);
        // render
        gll::render();

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        // render container
        myshader.use();
        vavbebo.bindVertexArray();
        if(type == 1){
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        else if(type == 2 || type == 3){
            if(type == 3){
                // Since we start the depth test, we need to clear the depth buffer of last frame
                glClear(GL_DEPTH_BUFFER_BIT);
            }
            model = glm::rotate(I4, glm::radians(50.0f)*float(glfwGetTime()), glm::vec3(0.5, 1.0, 0.0));
            myshader.setMat4f("model", model);    
        
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        else if(type >= 4)
        {
            glClear(GL_DEPTH_BUFFER_BIT);
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
            for(unsigned int i = 0; i < 10; i++)
            {
                model = glm::translate(I4, cubePositions[i]);
                float angle = 20.0f * i; 
                float k = 1.0f;
                if(type >= 5 && i % 3 == 0) {
                    k = static_cast<float>(glfwGetTime());
                }
                model = glm::rotate(model, glm::radians(angle) * k, glm::vec3(1.0f, 0.3f, 0.5f));
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
