#include <iostream>
#include <gl_util.h>

std::string proj_name = "07_learn_camera";

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


int main(int argc, char* argv[])
{
    gl_util::Window window(WIN_WIDTH, WIN_HEIGHT, "Window");
    window.enableDepthTest();

    gl_util::Shader myshader;
    myshader.load("../shaders/chapter_1/06.1.vs", "../shaders/chapter_1/06.1.fs");
    
    // --------------------------- Prase inputs -----------------------------
    unsigned char type = 0;
    // Check input
    if(argc < 2)
    {
        std::cout << proj_name << ":\n\tYou can input a integer to specify the different shader model, the support interger are:\n" << 
        "\t# 1, display square in dynamic view \n" << 
        "\t# 2, render 10 stationary square, using keyboard 'W-A-S-D-I-O' to move the GL camera position to 'UP-DOWN-LEFT-RIGHT-FORWARD-BACKWARD'\n" <<
        "\t# 3, render 10 stationry square, using mouse movement to change the orientation of camera view, and use mouse scroll to change the FOV\n";
        return 0;
    }
    else{
        type = std::stoi(argv[1]);
        if(type == 2){
            window.setKeyboardEventCallBack(processInput);
        }
        if(type >= 3){
            glfwSetScrollCallback(window.ptr(), scrollCallback);
            glfwSetCursorPosCallback(window.ptr(), mouseCallback);
            glfwSetInputMode(window.ptr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    // ------------------------------------------------------------------------
    
        
    float vertices[] = {
        // Vertices          // Texcoords
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
    gl_util::VAVBEBO vavbebo;
    vavbebo.bind(vertices, sizeof(vertices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    // load and create a texture 
    // -------------------------    
    gl_util::Texture2D texture0(0);
    if( !texture0.loadImage("../resources/container.jpg"))  return -2;
    gl_util::Texture2D texture1(1);
    if( !texture1.loadImage("../resources/awesomeface.png"))  return -2;
    //tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    myshader.use(); // don't forget to activate/use the shader before setting uniforms!
    myshader.setInt("texture1", texture0.ID());
    myshader.setInt("texture2", texture1.ID());

    
    glm::mat4 I4(1.0f), model, view, projection;
    projection = glm::perspective(glm::radians(45.0f), float(WIN_WIDTH)/float(WIN_HEIGHT), 0.2f, 100.0f);  
    myshader.setMat4f("projection", projection);


    // render loop
    // -----------
    while (!window.shouldClose())
    {
        float curr_time = glfwGetTime();
        delta_time = curr_time - prev_time;
        prev_time = curr_time;

        window.activate();
        window.clear();

        // Bind textures on corresponding texture units
        texture0.bind();
        texture1.bind();
        
        // Render container
        myshader.use();
        
        if(type >= 1){
            if(type == 1){
                float radius = 10.f;
                float posx = sin(glfwGetTime()) * radius;
                float posz = cos(glfwGetTime()) * radius;
                view = glm::lookAt(glm::vec3(posx, 0.0, posz), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
            }
            else if(type >= 2){
                view = camera.getViewMatrix();
                if(type >= 3){
                    projection = glm::perspective(glm::radians(camera.getFOV()), float(WIN_WIDTH)/float(WIN_HEIGHT), 0.2f, 100.0f);  
                    myshader.setMat4f("projection", projection);
                }

                // printf("T_view\n");
                // for(int i = 0; i < 4; i++){
                //     for(int j = 0; j < 4; j++){
                //         printf("%f,", view[i][j]);
                //     }
                //     printf("\n");
                // }
                // printf("T_projection\n");
                // for(int i = 0; i < 4; i++){
                //     for(int j = 0; j < 4; j++){
                //         printf("%f,", projection[i][j]);
                //     }
                //     printf("\n");
                // }
                // printf("\n");
                // static int count = 0;
                // if(++count >= 20) break;
            }
            myshader.setMat4f("view", view);
            
            vavbebo.bindVertexArray();
            for(unsigned int i = 0; i < 10; i++)
            {
                model = glm::translate(I4, cubePositions[i]);
                float angle = 20.0f * i; 
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                myshader.setMat4f("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            //printf("---- refrease ----\n");
        }
        window.refresh();
    }
    vavbebo.release();
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