#include <stdio.h>
#include <iostream>
#include <gl_util.h>

std::string proj_name = "test_multi_window";

int main(int argc, char* argv[])
{
    std::cout << proj_name << ":\n" << 
        "\tShow two GL windows, one render rectangle consists of two triangles with "
        "VAO, VBO, and EBO, another render the polygons render of rectangle\n"
        "Press 'Esc' to exit.\n";

    gl_util::Window window1(800, 600, "Window");
    gl_util::Window window2(600, 600, "Window");

    gl_util::Shader shader1, shader2;
    shader1.load("../shaders/chapter_1/02.1.vs", "../shaders/chapter_1/02.1.fs"); 
    shader2.load("../shaders/chapter_1/02.1.vs", "../shaders/chapter_1/02.1.fs"); 

    // Create vao, vbo, ebo to bind the vertices
    gl_util::VAVBEBO vavbebo1, vavbebo2;

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
    vavbebo1.bind(vertices, sizeof(vertices), indices, sizeof(indices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vavbebo2.bind(vertices, sizeof(vertices), indices, sizeof(indices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while(!window1.shouldClose() && !window2.shouldClose()){
        gl_util::clear();

        window1.activate();
        shader1.use();
        vavbebo1.bindVertexArray();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // use this when EBO exist

        window2.activate();
        shader2.use();
        vavbebo2.bindVertexArray();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        window1.refresh();
        window2.refresh();
    }

    return 0;
}
