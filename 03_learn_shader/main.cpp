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

    // Create vao, vbo, ebo to bind the vertices
    gll::VAVBEBO vavbebo;
    
    // Check input
    unsigned char type = 0;
    if(argc >= 2){
        type = std::stoi(argv[1]);
        if(type == 1){
            myshader.load("../textures/03.1.texture.vs", "../textures/03.1.texture.fs"); 
        }
        else if(type == 2){
            myshader.load("../textures/03.1.texture.vs", "../textures/03.2.texture.fs"); 
        }
        else if(type == 3){
            myshader.load("../textures/03.3.texture.vs", "../textures/03.3.texture.fs"); 
        }
        else if(type == 4){
            myshader.load("../textures/03.4.texture.vs", "../textures/03.3.texture.fs"); 
        }
    }
    else{
        printf("Please set an input arguments range in [1,4]\n");
        return 0;
    }
    // -------------------------------------------------------------------------
    
    if(type == 1 || type == 2){
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };
        vavbebo.bind(vertices, sizeof(vertices));
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        // Activate the VertexArrtrib by the position
        glEnableVertexAttribArray(0);
    }
    else if(type == 3 || type == 4)
    {
        float vertices[] = {
            // positions        // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
        };
        vavbebo.bind(vertices, sizeof(vertices));
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    // -------------------------------------------------------------------------

    // as we only have a single shader, we could also just activate our shader once beforehand if we want to 
    myshader.use();

    while(!glfwWindowShouldClose(window)){
        // Input
        gll::processInput(window);
        // Render
        gll::render();

        // Draw
        if(type == 2){
            float time_val = glfwGetTime();
            float green_val = (sin(time_val) / 2.0f + 0.5f);
            int vertex_color_location = glGetUniformLocation(myshader.ID, "my_color");
            glUniform4f(vertex_color_location, 0.0f, green_val, 0.0f, 1.0f);
        }
        else if(type == 4){
            myshader.setFloat("offset_x", 0.3f);
        }
        vavbebo.bindVertexArray(); 
        glDrawArrays(GL_TRIANGLES, 0, 3); // use this when only VAO exist

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vavbebo.release();
    myshader.release();
    glfwTerminate();
    return 0;
}
