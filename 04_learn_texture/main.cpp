#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>
#include "../gll_util/gll_util.h"

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

    unsigned char type = 0;
    // Check input
    if(argc >= 2){
        type = std::stoi(argv[1]);
        if(type == 1){
            myshader.load("../textures/04.1.texture.vs", "../textures/04.1.texture.fs");         
        }
        else if(type == 2){
            myshader.load("../textures/04.1.texture.vs", "../textures/04.2.texture.fs");
        }
        else if(type == 3){
            myshader.load("../textures/04.1.texture.vs", "../textures/04.3.texture.fs");
        }
    }
    else{
        printf("Please set an input arguments range in [1,3]\n");
        return 0;
    }
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    gll::VAVBEBO vavbebo;
    vavbebo.bind(vertices, sizeof(vertices), indices, sizeof(indices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    if( !gll::create2DTexture("../resources/container.jpg", GL_RGB, texture) ){
        return -2;
    }
    unsigned int texture2;
    if(type == 3){
        // texture 2
        if( !gll::create2DTexture("../resources/awesomeface.png", GL_RGBA, texture2)) {
            return -2;
        }

        //tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        myshader.use(); // don't forget to activate/use the shader before setting uniforms!
        // either set it manually like so:
        glUniform1i(glGetUniformLocation(myshader.ID, "texture1"), 0);
        // or set it via the texture class
        myshader.setInt("texture2", 1);
    }  

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        gll::processInput(window);
        // render
        gll::render();

        // bind textures on corresponding texture units
        if(type == 3){
            glActiveTexture(GL_TEXTURE0);
        }
        glBindTexture(GL_TEXTURE_2D, texture);
        if(type == 3){
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
        }

        // render container
        myshader.use();
        vavbebo.bindVertexArray();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vavbebo.release();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
