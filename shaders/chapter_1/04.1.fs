#version 330 core
out vec4 frag_color;

in vec3 my_color;
in vec2 my_tex_coord;

// texture sampler
uniform sampler2D my_texture;

void main()
{
    frag_color = texture(my_texture, my_tex_coord);
}