# Learn OpenGL

This repository stores the history codes when I learned OpenGL.
A brilliant website for starting programming with OpenGL can be found in [<b>LearnOpenGL</b>](https://learnopengl-cn.github.io/).

## Notes

The useful webesit for learning OpenGL furtherly.
- [OpenGL Tutorial - Useful Tools & Links](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/)

To better understand GLSL, the website below are optional.
- [知乎：GL Shader Language（GLSL）详解-基础语法](https://zhuanlan.zhihu.com/p/349296191)

### About practices

+ [01_hello_window](https://github.com/wlfrii/learn_OpenGL/tree/main/01_hello_window) learned the creation of an GL window. What should be __NOTICED__ is that the GLAD should be initialized before calling any GL interface.
<i>Here I tried to initialize GLAD before I created a GLFW window, but it is not work.</i>

+ [02_hello_triangle](https://github.com/wlfrii/learn_OpenGL/tree/main/02_hello_triangle) learned the basic skills about the GL shader. The most important part I got is the difference between VAO+VBO and VAO+VBO+EBO, and the application of those.
For example, VAO+VBO -> [<font color=purple> _glDrawArrays_ </font>](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml), VAO+VBO+EBO -> [<font color=purple> _glDrawElements_</font>](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawElements.xhtml).
To draw in wireframe polygons, calling [<font color=purple> _glPolygonMode_</font>](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glPolygonMode.xhtml).

+ [03_learn_shader](https://github.com/wlfrii/learn_OpenGL/tree/main/03_learn_shader), one of the most important topic I think, learned the use of __GLSL__, especially _uniform_ variable in vertex shader. What's more, I start to konw the usefullness of  [<font color=purple> _glVertexAttribPointer_</font>](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml) and [<font color=purple> _glEnableVertexAttribArray_</font>](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml).
__GLSL__ is a very important way that we can communicate with the graphics.

+ [04_learn_texture](https://github.com/wlfrii/learn_OpenGL/tree/main/04_learn_texture), one of the most important topic I think, deeply understand [<font color=purple> _glVertexAttribPointer_</font>](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml), learned how to correspond the loaded texture and texture coordinate, and the relation between vertex position and texture coordinate. 

+ [05_learn_glm](https://github.com/wlfrii/learn_OpenGL/tree/main/05_learn_glm) learned the basic use of [GLM](https://glm.g-truc.net/0.9.8/index.html) library; learned how to move the texture by transmit GLM matrices to vertex shader by _uniform_ variable.
Note, the download GLM library not include the `ext` header files in the `glm.hpp`, so to easy the use of GLM, we should manually include `ext.hpp` in `glm.hpp`. After that, only `glm.hpp` should be included when the library is required.

+ [06_learn_coordinate](https://github.com/wlfrii/learn_OpenGL/tree/main/06_learn_coordinate) learned the components in GL, which includes _model_, _view_, _projection_. 
A important function <font color=purple>GL_DEPTH_TEST</font> should be enable, which can create a __Z buffer__, also known as __Depth Buffer__, to determine whether a __texel__ should be rendered. When enable this function, <font color=purple>GL_DEPTH_BUFFER_BIT</font> should be clear before render each new frame.

+ [07_learn_camera](https://github.com/wlfrii/learn_OpenGL/tree/main/07_learn_camera) learned the use of view(camera) matrix, that can adjust the view direction in OpenGL. However, there are a lot of limitation when describe the rotation by Euler Angles.
Note the z-axis of camera coordinate is directed from screen to viewer, so if we want the camera move away from the model, we need to increase z-axis value.