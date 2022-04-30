#include <iostream>
#include "../gl_util/gl_util.h"

std::string proj_name = "06_learn_coordinate";

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;

int main(int argc, char* argv[])
{
    gl_util::Window window(WIN_WIDTH, WIN_HEIGHT);
    
    gl_util::Shader myshader;
    myshader.load("../shaders/06.1.vs", "../shaders/06.1.fs");
    
    gl_util::VAVBEBO vavbebo;
    // --------------------------- Prase inputs -----------------------------
    unsigned char type = 0;
    // Check input
    if(argc < 2)
    {
        std::cout << proj_name << ":\n\tYou can input a integer to specify the different shader model, the support interger are:\n" << 
        "\t# 1, render two texture, and set model, view, projection for the vertices\n" << 
        "\t# 2, render a square consist of 36 vertices and texcoords and rotated with time goes on. Each plane of the square is rendered with two textures. NOTE, this dynamic square may looks weird\n" <<
        "\t# 3, based on # 2, enable the depth test so that OpenGL can know which pixel should be show and which should be hidden\n" <<
        "\t# 4, based on # 3, change the position of square, then render 10 fixed squares simultaneously\n" << 
        "\t# 5, based on # 3, change the position of square, then render 10 rotated squares simultaneously\n";
        return 0;
    }
    else{
        type = std::stoi(argv[1]);
        if(type == 1){
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
            vavbebo.bind(vertices, sizeof(vertices), indices, sizeof(indices));
        }
        else if(type >= 2){
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
            vavbebo.bind(vertices, sizeof(vertices));

            if(type >= 3){
                // glEnable() and glDisable() allows we enable or disable a function
                window.enableDepthTest();
            }
        }  
    }
    // ------------------------------------------------------------------------

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


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
    model = glm::rotate(I4, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
    myshader.setMat4f("model", model);
    
    view = glm::translate(I4, glm::vec3(0.0f, 0.0f, -3.0f));
    myshader.setMat4f("view", view);

    projection = glm::perspective(glm::radians(45.0f), float(WIN_WIDTH)/float(WIN_HEIGHT), 0.2f, 100.0f);  
    myshader.setMat4f("projection", projection);
    
    // render loop
    // -----------
    while (!window.shouldClose())
    {
        window.activate();

        // The depth buffer will also be clear once we enable depth test
        window.clear();

        // bind textures on corresponding texture units
        texture0.bind();
        texture1.bind();
        
        // render container
        myshader.use();
        vavbebo.bindVertexArray();
        if(type == 1){
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        else if(type == 2 || type == 3){
            model = glm::rotate(I4, glm::radians(50.0f)*float(glfwGetTime()), glm::vec3(0.5, 1.0, 0.0));
            myshader.setMat4f("model", model);    
        
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        else if(type >= 4)
        {
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
            for(unsigned int i = 0; i < 10; i++)
            {
                model = glm::translate(I4, cubePositions[i]);
                float k = 1.0f;
                if(type >= 5) {
                    k = static_cast<float>(glfwGetTime());
                }
                float angle = glm::radians(20.0f * (i + 1)) * k; 
                model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
                myshader.setMat4f("model", model);

                //gl_util::print("Model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
        window.refresh();
    }
    vavbebo.release();
    window.release();
    
    return 0;
}
