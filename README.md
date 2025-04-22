# Learn OpenGL

This repository stores the history codes when I learned OpenGL.
A brilliant website for starting programming with OpenGL can be found in [<b>LearnOpenGL</b>](https://learnopengl-cn.github.io/).

## Notes

The useful webesit for learning OpenGL furtherly.
- [OpenGL Tutorial - Useful Tools & Links](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/)

To better understand GLSL, the website below are optional.
- [知乎：GL Shader Language（GLSL）详解-基础语法](https://zhuanlan.zhihu.com/p/349296191)

### Write in Front

+ GLFM: [https://www.glfw.org/download.html](https://www.glfw.org/download.html)
+ GLAD: [https://glad.dav1d.de/](https://glad.dav1d.de/)
+ GLM:  [https://glm.g-truc.net/0.9.9/index.html](https://glm.g-truc.net/0.9.9/index.html)

After learning the basic part of OpenGL, I find that there are excessive similar even same codes when doing the practices frome the online chapter, so I refactor those codes into [gl_util](https://github.com/wlfrii/learn_OpenGL/tree/main/gl_util) folder.

The [gl_util](https://github.com/wlfrii/learn_OpenGL/tree/main/gl_util) will be very helpful to the later practices, including:
 + [`gl_util::Window`](https://github.com/wlfrii/learn_OpenGL/blob/main/gl_util/gl_util/gl_window.h). A class degsigned to manage GLFWwindow.
 + [`gl_util::VAVBEBO`](https://github.com/wlfrii/learn_OpenGL/blob/main/gl_util/gl_util/gl_vavbebo.h) A manager for VAO, VBO, and EBO.
 + [`gl_util::Shader`](https://github.com/wlfrii/learn_OpenGL/blob/main/gl_util/gl_util/gl_shader.h) A manager for shader program object.
 + [`gl_util::Texture2D`](https://github.com/wlfrii/learn_OpenGL/blob/main/gl_util/gl_util/gl_texture.h) A manager for the GL texture.

### About practices

+ [1_01_hello_window](https://github.com/wlfrii/learn_OpenGL/tree/main/1_01_hello_window) learned the creation of an OpenGL window. What should be __NOTICED__ is that the GLAD should be initialized before calling any OpenGL interface.
<i>Here I tried to initialize GLAD before I created a GLFW window, but it is not work.</i>

+ [1_02_hello_triangle](https://github.com/wlfrii/learn_OpenGL/tree/main/1_02_hello_triangle) learned the basic skills about the GL shader. The most important part I got is the difference between VAO+VBO and VAO+VBO+EBO, and the application of those.
For example, VAO+VBO -> [`glDrawArrays`](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml), VAO+VBO+EBO -> [`glDrawElements`](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawElements.xhtml).
To draw in wireframe polygons, calling [`glPolygonMode`](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glPolygonMode.xhtml).

+ [1_03_learn_shader](https://github.com/wlfrii/learn_OpenGL/tree/main/1_03_learn_shader), one of the most important topic I think, learned the use of __GLSL__, especially _uniform_ variable in vertex shader. What's more, I start to konw the usefullness of  [`glVertexAttribPointer`](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml) and [`glEnableVertexAttribArray`](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml).
__GLSL__ is a very important way that we can communicate with the graphics.

+ [1_04_learn_texture](https://github.com/wlfrii/learn_OpenGL/tree/main/1_04_learn_texture), one of the most important topic I think, deeply understand [`glVertexAttribPointer`](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml), learned how to correspond the loaded texture and texture coordinate, and the relation between vertex position and texture coordinate. 

+ [1_05_learn_glm](https://github.com/wlfrii/learn_OpenGL/tree/main/1_05_learn_glm) learned the basic use of [GLM](https://glm.g-truc.net/0.9.9/index.html) library; learned how to move the texture by transmit GLM matrices to vertex shader by _uniform_ variable.
Note, the download GLM library not include the `ext` header files in the `glm.hpp`, so to easy the use of GLM, we should manually include `ext.hpp` in `glm.hpp`. After that, only `glm.hpp` should be included when the library is required.

+ [1_06_learn_coordinate](https://github.com/wlfrii/learn_OpenGL/tree/main/1_06_learn_coordinate) learned the components in GL, which includes _model_, _view_, _projection_. 
A important function <font color=purple>GL_DEPTH_TEST</font> should be enable, which can create a __Z buffer__, also known as __Depth Buffer__, to determine whether a __texel__ should be rendered. When enable this function, <font color=purple>GL_DEPTH_BUFFER_BIT</font> should be clear before render each new frame.

+ [1_07_learn_camera](https://github.com/wlfrii/learn_OpenGL/tree/main/1_07_learn_camera) learned the use of view(camera) matrix, that can adjust the view direction in OpenGL. However, there are a lot of limitation when describe the rotation by Euler Angles.
Note the z-axis of camera coordinate is directed from screen to viewer, so if we want the camera move away from the model, we need to increase z-axis value.
A very important details of projection matrix can be found in [<b>OpenGL Projection Matrix</b>](http://www.songho.ca/opengl/gl_projectionmatrix.html).

+ [2_01_learn_color](https://github.com/wlfrii/learn_OpenGL/tree/main/2_01_learn_color) start to know the foundation of color and light in OpenGL world. 
The symbol $*$ for two vector in OpenGL denotes elements-multiplication.

+ [2_02_learn_lighting](https://github.com/wlfrii/learn_OpenGL/tree/main/2_02_learn_lighting) learned that three important lighting components are required in OpenGL, which are AMBIENT_LIGHTING, DIFFUSE_LIGHTING, and SPECULAR_HIGHLIGHT.
Secondly, the normal of the vertice are the key to calculate DIFFUSE_LIGHTING.
The Normal Matrix is defined as "the transpose of the inverse of the left-top of the Model Matrix".
Thirdly, the strength of AMBIENT_LIGHTING, SPECULAR_LIGHTING, and Shininess of Highlight can be furtherly understand after doing the practices.