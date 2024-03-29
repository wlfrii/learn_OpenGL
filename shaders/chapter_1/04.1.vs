#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex_coord;

out vec3 my_color;
out vec2 my_tex_coord;

void main()
{
    gl_Position = vec4(pos, 1.0);
    my_color = color;
    my_tex_coord = tex_coord;
}