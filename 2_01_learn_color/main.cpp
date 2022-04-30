#include <iostream>
#include "../gl_util/gl_util.h"

std::string proj_name = "08_learn_color";

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;


void processInput(GLFWwindow *window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);


gl_util::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float xprev = WIN_WIDTH / 2;
float yprev = WIN_HEIGHT / 2;

float delta_time = 0;
float prev_time = 0;
float fov = 45.0f;

int main(int argc, char* argv[])
{
    std::cout << proj_name << ":\n\tDisplay a square with specified color. There is also a light cube represent the light source. Using 'W-A-S-D-I-O' key or mouse to move camera view.\n";
    
    gl_util::Window window(WIN_WIDTH, WIN_HEIGHT);
    window.enableDepthTest();
    window.setKeyboardEventCallBack(processInput);
    
    glfwSetCursorPosCallback(window.get(), mouseCallback);
    glfwSetScrollCallback(window.get(), scrollCallback);
    glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    gl_util::Shader light_shader;
    light_shader.load("../shaders/chapter_2/01.1.vs", "../shaders/chapter_2/01.2.fs");
    gl_util::Shader cube_shader;
    cube_shader.load("../shaders/chapter_2/01.1.vs", "../shaders/chapter_2/01.1.fs");

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        0.5f, -0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f, 
        0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
    gl_util::VAVBEBO light_vavbo;
    light_vavbo.bind(vertices, sizeof(vertices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    gl_util::VAVBEBO cube_vavbo;
    cube_vavbo.bind(vertices, sizeof(vertices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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

        // Draw the model square
        glm::mat4 model(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        cube_shader.setMat4f("projection", projection);
        cube_shader.setMat4f("view", view);
        cube_shader.setMat4f("model", model);

        cube_vavbo.bindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // Draw the light square
        light_shader.use();
        light_shader.setMat4f("projection", projection);
        light_shader.setMat4f("view", view);
        model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
        model = glm::scale(model, glm::vec3(0.2));
        light_shader.setMat4f("model", model);
        
        light_vavbo.bindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.refresh();
    }

    light_vavbo.release();
    cube_vavbo.release();
    window.release();

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

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    static bool is_first = true;
    if(is_first){
        xprev = xpos;
        yprev = ypos;
        is_first = false;
    }
    float xoffset = xpos - xprev;
    float yoffset = yprev - ypos;
    xprev = xpos;
    yprev = ypos;
    camera.processMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}