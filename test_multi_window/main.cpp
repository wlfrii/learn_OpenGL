#include <stdio.h>
#include <iostream>
#include <gl_util.h>
#include <vector>

std::string proj_name = "test_multi_window";

float vertices[] = {
    // positions         // texture coords
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

std::vector<glm::vec3> cube_positions = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 6.5f,  1.0f, -15.0f),
    glm::vec3(-1.2f, -1.2f, -2.5f), 
    glm::vec3(-4.8f, -1.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f), 
    glm::vec3(-0.7f,  3.1f, -7.5f),
    glm::vec3( 1.3f, -1.7f, -3.5f),
    glm::vec3( 1.5f,  2.0f, -4.0f),
    glm::vec3(-1.5f,  1.0f, -3.0f) 
};

int main(int argc, char* argv[])
{
    std::cout << proj_name << ":\n" << 
        "\tShow two GL windows for multi window test.\n"
        "Press 'Esc' to exit.\n";

    gl_util::Window window1(800, 600, "Window1", true);
    window1.enableDepthTest();
    gl_util::VAVBEBO vavbebo1;
    vavbebo1.bind(vertices, sizeof(vertices), {3, 2});

    gl_util::Texture2D texture0(0);
    if( !texture0.loadImage("../resources/container.jpg"))  return -2;
    gl_util::Texture2D texture1(1);
    if( !texture1.loadImage("../resources/awesomeface.png"))  return -2;
    glm::mat4 I4(1.0f), model, view, projection;
    model = glm::rotate(I4, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
    view = glm::translate(I4, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), float(8)/float(6), 0.2f, 100.0f); 
    
    gl_util::Shader shader1;
    shader1.load("../shaders/chapter_1/06.1.vs", "../shaders/chapter_1/06.1.fs");
    shader1.use(); // don't forget to activate/use the shader before setting uniforms!
    shader1.setInt("texture1", texture0.ID());
    shader1.setInt("texture2", texture1.ID());    
    shader1.setMat4f("model", model);
    shader1.setMat4f("view", view);
    shader1.setMat4f("projection", projection);

    gl_util::Window window2(600, 600, "Window2", true);
    window2.enableDepthTest();
    gl_util::VAVBEBO vavbebo2;
    vavbebo2.bind(vertices, sizeof(vertices), {3, 2});

    while(!window1.shouldClose() || !window2.shouldClose()){
        window1.clear();
        texture0.bind();
        texture1.bind();
        shader1.use();
        vavbebo1.bindVertexArray();
        model = glm::rotate(I4, glm::radians(50.0f)*float(glfwGetTime()), glm::vec3(0.5, 1.0, 0.0));
        shader1.setMat4f("model", model);    
        glDrawArrays(GL_TRIANGLES, 0, 36);
        window1.refresh();

        window2.clear();
        texture0.bind();
        texture1.bind();
        shader1.use();
        vavbebo2.bindVertexArray();
        for(unsigned int i = 0; i < cube_positions.size(); i++) {
            model = glm::translate(I4, cube_positions[i]);
            float k = static_cast<float>(glfwGetTime());
            float angle = glm::radians(20.0f * (i + 1)) * k; 
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            shader1.setMat4f("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        window2.refresh();

        glfwPollEvents();
    }

    return 0;
}
