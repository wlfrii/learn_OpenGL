#include <iostream>
#include <gl_util.h>

std::string proj_name = "2_02_learn_lighting";

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;
 
void processInput(GLFWwindow *window);

gl_util::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float xprev = WIN_WIDTH / 2;
float yprev = WIN_HEIGHT / 2;

float delta_time = 0;
float prev_time = 0;
float fov = 45.0f;

int main(int argc, char* argv[])
{
    std::cout << proj_name << "\n"
        "\tSimilar to previous project. Display two square, one for model, and another "
        "for light source. This project consider the ambient light, diffuse, and "
        "specular reflection, so that the model looks more real. You can change the "
        "strength of these light effects in 0.9.1.vs to see the lighting effects.\n"
        "Press 'Esc' to exit.\n";

    gl_util::Window window(WIN_WIDTH, WIN_HEIGHT, "Window");
    window.enableDepthTest();
    window.setKeyboardEventCallBack(processInput);
    
    gl_util::Shader light_shader;
    light_shader.load("../shaders/chapter_2/02.2.vs", "../shaders/chapter_2/02.2.fs");
    gl_util::Shader cube_shader;
    cube_shader.load("../shaders/chapter_2/02.1.vs", "../shaders/chapter_2/02.1.fs");

    float vertices[] = {
        // Vertices           // Normals
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    gl_util::VAVBEBO light_vavbo;
    light_vavbo.bind(vertices, sizeof(vertices), {3, 3});
    
    gl_util::VAVBEBO cube_vavbo;
    cube_vavbo.bind(vertices, sizeof(vertices), {3, 3});


    glm::vec3 light_pos(0.2f, 0.0f, 2.0f);
    // render loop
    // -----------
    while (!window.shouldClose())
    {
        float curr_time = glfwGetTime();
        delta_time = curr_time - prev_time;
        prev_time = curr_time;
        
        window.activate();
        window.clear();
        
        // render container
        cube_shader.use();
        cube_shader.setVec3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        cube_shader.setVec3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        cube_shader.setVec3f("light_pos", light_pos);
        cube_shader.setVec3f("view_pos", camera.getPosition());

        glm::mat4 model(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        cube_shader.setMat4f("projection", projection);
        cube_shader.setMat4f("view", view);
        cube_shader.setMat4f("model", model);

        cube_vavbo.bindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        light_shader.use();
        light_shader.setMat4f("projection", projection);
        light_shader.setMat4f("view", view);
        model = glm::translate(model, light_pos);
        model = glm::scale(model, glm::vec3(0.2));
        light_shader.setMat4f("model", model);
        
        light_vavbo.bindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.refresh();
    }

    return 0;
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(gl_util::Camera::MOVE_UP, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(gl_util::Camera::MOVE_DOWN, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(gl_util::Camera::MOVE_LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(gl_util::Camera::MOVE_RIGHT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        camera.processKeyboard(gl_util::Camera::MOVE_FORWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        camera.processKeyboard(gl_util::Camera::MOVE_BACKWARD, delta_time);
}
