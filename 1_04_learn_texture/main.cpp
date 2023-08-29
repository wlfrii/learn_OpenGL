#include <iostream>
#include "../gl_util/gl_util.h"

std::string proj_name = "04_learn_texture";

int main(int argc, char* argv[])
{
    gl_util::Window window(800, 600, "Window");

    gl_util::Shader myshader;

    // --------------------------- Prase inputs -----------------------------
    unsigned char type = 0;
    // Check input
    if(argc < 2)
    {
        std::cout << proj_name << ":\n\tYou can input a integer to specify the different shader model, the support interger are:\n" << 
        "\t# 1, set vertices, colors, and texcoords when binding VAVBEBO, and transmit texcoords from vertex shader to fragment shader. Then render a texture (from image) w.r.t texcoords\n" << 
        "\t# 2, based on # 1, transmit color from vertex shader to fragment shader, and combine the texels color and vertices color\n" <<
        "\t# 3, based on # 1, render two texture w.r.t texcoords and mix the color in each pixel by 0.8*texture1 + 0.2*texture2\n" << 
        "\t# 4, opposite the direction of texture2 in # 3\n";
        return 0;
    }
    else{
        type = std::stoi(argv[1]);
        if(type == 1){
            myshader.load("../shaders/chapter_1/04.1.vs", "../shaders/chapter_1/04.1.fs");         
        }
        else if(type == 2){
            myshader.load("../shaders/chapter_1/04.1.vs", "../shaders/chapter_1/04.2.fs");
        }
        else if(type == 3){
            myshader.load("../shaders/chapter_1/04.1.vs", "../shaders/chapter_1/04.3.fs");
        }
        else if(type == 4 || type == 5){
            myshader.load("../shaders/chapter_1/04.1.vs", "../shaders/chapter_1/04.4.fs");
        }
    }
    // -------------------------------------------------------------------------

    gl_util::VAVBEBO vavbebo;
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
    vavbebo.bind(vertices, sizeof(vertices), indices, sizeof(indices));

    // ------------------------------------------------------------------------

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
    gl_util::Texture2D texture0(0);
    if(!texture0.loadImage("../resources/container.jpg")) return -2;
    gl_util::Texture2D texture1(1);
    if(type == 3 || type == 4){
        if(!texture1.loadImage("../resources/awesomeface.png")) return -3;
    
        //tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        myshader.use(); // don't forget to activate/use the shader before setting uniforms!
        // either set it manually like so:
        myshader.setInt("texture1", texture0.ID());
        // glUniform1i(glGetUniformLocation(myshader.ID, "texture1"), 0);
        // or set it via the texture class
        myshader.setInt("texture2", texture1.ID());
    }  

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        window.activate();
        window.clear();

        // bind textures on corresponding texture units
        texture0.bind();
        if(type == 3 || type == 4){
            texture1.bind();
        }

        // render container
        myshader.use();
        vavbebo.bindVertexArray();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.refresh();
    }

    vavbebo.release();
    window.release(); 
    
    return 0;
}
