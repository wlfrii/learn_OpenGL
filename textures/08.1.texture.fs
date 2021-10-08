#version 330 core

out vec4 outFragColor;

// texture sampler
uniform vec3 objectColor;
uniform vec3 lightColor;

// texture() -- retrieve texels from a texture at tex_coord position
// and then store the texels in the corresponding samplerND

void main()
{
    outFragColor = vec4(lightColor * objectColor, 1.0);
}