#include <iostream>
#include <gl_util.h>

std::string proj_name = "1_05_learn_glm";

int main(int argc, char* argv[])
{
    std::cout << proj_name << "\n"
        "\tDisplay two mixed textures, one in left top and another located at right "
        "down. Both the mixed texutures are active, since a transformation matrix "
        "parameterized by time is set to transform the vertices position\n"
        "Press 'Esc' to exit.\n";

    gl_util::Window window(800, 600, "Window");
    gl_util::Shader myshader;
    myshader.load("../shaders/chapter_1/05.1.vs", "../shaders/chapter_1/05.1.fs");

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
    gl_util::VAVBEBO vavbebo;
    vavbebo.bind(vertices, sizeof(vertices), {3, 2}, indices, sizeof(indices));

    // load and create a texture 
    // -------------------------
    gl_util::Texture2D texture0(0);
    if(!texture0.loadImage("../resources/container.jpg")) return -2;
    gl_util::Texture2D texture1(1);
    if(!texture1.loadImage("../resources/awesomeface.png")) return -3;
    
    //tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    myshader.use(); // don't forget to activate/use the shader before setting uniforms!
    myshader.setInt("texture1", texture0.ID());
    myshader.setInt("texture2", texture1.ID());

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        window.activate();
        window.clear();

        // bind textures on corresponding texture units
        texture0.bind();
        texture1.bind();

        // render container
        myshader.use();
        vavbebo.bindVertexArray();
        
        // Draw left top box
        glm::mat4 trans(1.0);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        myshader.setMat4f("transform", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Render right down box
        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5, 0.5, 0.0));
        float scale = sin(glfwGetTime());
        trans = glm::scale(trans, glm::vec3(scale, scale, scale));
        myshader.setMat4f("transform", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        window.refresh();
    }

    return 0;
}
