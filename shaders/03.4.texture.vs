#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 vertex_color;

uniform float offset_x;

void main()
{
    gl_Position = vec4(pos.x + offset_x, pos.y, pos.z, 1.0);
    vertex_color = color;
}