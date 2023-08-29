#include <stdio.h>
#include <iostream>
#include "../gl_util/gl_util.h"

std::string proj_name = "03_learn_shader";

int main(int argc, char* argv[])
{
    gl_util::Window window(800, 600, "Window");

    gl_util::Shader myshader;
    gl_util::VAVBEBO vavbebo;
    
    // --------------------------- Prase inputs -----------------------------
    unsigned char type = 0;
    if(argc < 2)
    {
        std::cout << proj_name << ":\n\tYou can input a integer to specify the different shader model, the support interger are:\n" << 
        "\t# 1, use default color in vertex shader, and transmit it to fragment shader\n" << 
        "\t# 2, set dynamic color to fragment shader\n" <<
        "\t# 3, set color when bind VAVBEBO and transmit the color from vertex shader to fragment shader\n" << 
        "\t# 4, based on 3, set deviation for x position of object in vertex shader\n";
        return 0;
    }
    else{
        type = std::stoi(argv[1]);
        if(type == 1){
            myshader.load("../shaders/chapter_1/03.1.vs", "../shaders/chapter_1/03.1.fs");
        }
        else if(type == 2){
            myshader.load("../shaders/chapter_1/03.1.vs", "../shaders/chapter_1/03.2.fs"); 
        }
        else if(type == 3){
            myshader.load("../shaders/chapter_1/03.3.vs", "../shaders/chapter_1/03.3.fs"); 
        }
        else if(type == 4){
            myshader.load("../shaders/chapter_1/03.4.vs", "../shaders/chapter_1/03.3.fs"); 
        }
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

    // As we only have a single shader, we could also just activate our shader once beforehand if we want to 
    myshader.use();

    while(!window.shouldClose()){
        gl_util::clear();
        window.activate();

        // Draw
        if(type == 2){
            float time_val = glfwGetTime();
            float green_val = (sin(time_val) / 2.0f + 0.5f);
            myshader.setFloat4("my_color", 0.0f, green_val, 0.0f, 1.0f);
        }
        else if(type == 4){
            myshader.setFloat("offset_x", 0.3f);
        }
        vavbebo.bindVertexArray(); 
        glDrawArrays(GL_TRIANGLES, 0, 3); // use this when only VAO exist

        window.refresh();
    }
    vavbebo.release();
    myshader.release();
    window.release();

    return 0;
}
