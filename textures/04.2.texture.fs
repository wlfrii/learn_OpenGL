#version 330 core
out vec4 frag_color;

in vec3 my_color;
in vec2 my_tex_coord;

// texture sampler
uniform sampler2D my_texture;

// texture() -- retrieve texels from a texture at tex_coord position
// and then store the texels in the corresponding samplerND

void main()
{
    frag_color = texture(my_texture, my_tex_coord) * vec4(my_color, 1.0);
}