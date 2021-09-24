#include "../gll_util/gll_util.h"


int main()
{
    gll::initGLFW();
    GLFWwindow* window = gll::createGLFWwindow();
    if(!window) 
        return -2;  
    if( !gll::initGLAD() ) 
        return -1;

    glViewport(0, 0, 800, 600);

    while(!glfwWindowShouldClose(window)){
        // Input
        gll::processInput(window);
        // Render
        gll::render();

        // Check the mouse/keyboard events
        glfwPollEvents();
        // Store the color of each pixel in GLFW window
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}