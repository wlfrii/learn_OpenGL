#include <stdio.h>
#include <iostream>
#include <gl_util.h>

std::string proj_name = "1_02_hello_triangle";

int main(int argc, char* argv[])
{
    std::cout << proj_name << ":\n" << 
        "\tYou can input a integer to specify the different triangle model, "
        "the supported interger are:\n" 
        "\t - 1, for render a single triangle with only VAO and VBO\n" 
        "\t - 2, for render rectangle consists of two triangles with VAO, VBO, and EBO\n"
        "\t - 3, for polygons render of # 2\n" 
        "\t - 4, for render two triangles with VAO, VBO, and EBO\n"
        "Press 'Esc' to exit.\n";
    if(argc <= 1){
        return 0;
    }

    gl_util::Window window(800, 600, "Window");

    gl_util::Shader myshader;
    myshader.load("../shaders/chapter_1/02.1.vs", "../shaders/chapter_1/02.1.fs"); 

    // Create vao, vbo, ebo to bind the vertices
    gl_util::VAVBEBO vavbebo;
    
    // --------------------------- Prase inputs -----------------------------
    // Set up vertex data (and buffers) and configure vertex attributes based on the input
    unsigned int type = std::stoi(argv[1]);
    if(type == 1){ 
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };
        vavbebo.bind(vertices, sizeof(vertices), {3});
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
        vavbebo.bind(vertices, sizeof(vertices), {3}, indices, sizeof(indices));
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
        vavbebo.bind(vertices, sizeof(vertices), {3}, indices, sizeof(indices));
    }
    // -------------------------------------------------------------------------

    while(!window.shouldClose()){
        window.activate();
        window.clear();

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

    return 0;
}
