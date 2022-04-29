#include <stdio.h>
#include <iostream>
#include "../gl_util/gl_util.h"

std::string proj_name = "02_hello_triangle";

int main(int argc, char* argv[])
{
    gl_util::Window window(800, 600);

    gl_util::Shader myshader;
    myshader.load("../shaders/02.1.vs", "../shaders/02.1.fs"); 

    // Create vao, vbo, ebo to bind the vertices
    gl_util::VAVBEBO vavbebo;
    
    // --------------------------- Prase inputs -----------------------------
    // Set up vertex data (and buffers) and configure vertex attributes based on the input
    unsigned int type = 0;
    if(argc <= 1){
        std::cout << proj_name << ":\n\tYou can input a integer to specify the different triangle model, the support interger are:\n" << 
        "\t# 1, for render a single triangle with only VAO and VBO\n" << 
        "\t# 2, for render rectangle consists of two triangles with VAO, VBO, and EBO\n" <<
        "\t# 3, for polygons render of # 2\n" << 
        "\t# 4, for render two triangles with VAO, VBO, and EBO\n";
        return 0;
    }
    else{
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
    // -------------------------------------------------------------------------

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while(!window.shouldClose()){
        gl_util::clear();

        window.activate();

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

        window.refresh();
    }

    vavbebo.release();
    myshader.release();
    window.release();
    return 0;
}
