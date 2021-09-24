#include <stdio.h>
#include "../gll_util/gll_util.h"

int main(int argc, char* argv[])
{
    gll::initGLFW();
    GLFWwindow* window = gll::createGLFWwindow();
    if(!window) 
        return -2;  
    if( !gll::initGLAD() ) 
        return -1;

    gll::Shader myshader;
    myshader.load("../textures/02.1.texture.vs", "../textures/02.1.texture.fs"); 

    // Create vao, vbo, ebo to bind the vertices
    gll::VAVBEBO vavbebo;
    
    // Set up vertex data (and buffers) and configure vertex attributes based on the input
    unsigned int type = 0;
    if(argc >= 2){
        type = std::stoi(argv[1]);
        if(type == 1){ // ------------------------------
            float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f,  0.5f, 0.0f
            };
            vavbebo.bind(vertices, sizeof(vertices));
        }
        else if(type == 2 || type == 3){ 
            float vertices[] = {
                0.5f, 0.5f, 0.0f,   // right top
                0.5f, -0.5f, 0.0f,  // right bottom
                -0.5f, -0.5f, 0.0f, // left bottom
                -0.5f, 0.5f, 0.0f   // left top
            };
            unsigned int indices[] = {
                0, 1, 3, // fist triangle
                1, 2, 3  // second triangle
            };
            vavbebo.bind(vertices, sizeof(vertices), indices, sizeof(indices));
        }
        else{
            float vertices[] = {
                0.6f, 0.0f, 0.0f,
                0.3f, 0.5f, 0.0f,
                0.0f, 0.0f, 0.0f,
                -0.3f, 0.5f, 0.0f,
                -0.6f, 0.0f, 0.0f
            };
            GLuint indices[] = {
                0, 1, 2,
                2, 3, 4
            };
            vavbebo.bind(vertices, sizeof(vertices), indices, sizeof(indices));
        }
    }
    else{
        printf("Please set an input arguments range in [1,4]\n");
        return 0;
    }
    // -------------------------------------------------------------------------

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    // Activate the VertexArrtrib by the position
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)){
        // Input
        gll::processInput(window);
        // Render
        gll::render();

        // Draw
        myshader.use();
        vavbebo.bindVertexArray();
        if(type == 1){
            glDrawArrays(GL_TRIANGLES, 0, 3); // use this when only VAO exist
        }
        else{
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // use this when EBO exist
            if(type == 3){
                // draw in wireframe polygons
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
        }
        //glBindVertexArray(0); // unbind, but no need to unbind it every time

        // Check the mouse/keyboard events
        glfwPollEvents();
        // Store the color of each pixel in GLFW window
        glfwSwapBuffers(window);
    }

    vavbebo.release();
    myshader.release();
    glfwTerminate();
    return 0;
}
