#version 330 core
out vec4 frag_color;

in vec3 my_color;
in vec2 my_tex_coord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

// texture() -- retrieve texels from a texture at tex_coord position
// and then store the texels in the corresponding samplerND

void main()
{
    frag_color = mix(texture(texture1, my_tex_coord), texture(texture2, my_tex_coord), 0.2);
}