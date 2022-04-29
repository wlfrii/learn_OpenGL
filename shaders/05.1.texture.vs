#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex_coord;

out vec2 my_tex_coord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(pos, 1.0);
    my_tex_coord = vec2(tex_coord.x, 1.0 - tex_coord.y);
}