#version 330 core

in vec3 normal;
in vec3 frag_pos;

out vec4 outFragColor;

uniform vec3 light_pos;
uniform vec3 view_pos;

// texture sampler
uniform vec3 objectColor;
uniform vec3 lightColor;

// texture() -- retrieve texels from a texture at tex_coord position
// and then store the texels in the corresponding samplerND

void main()
{
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * lightColor;

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specular_strength = 0.8;
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32); // 32 means Shininess of the highlight
    vec3 specular = specular_strength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    outFragColor = vec4(result, 1.0);
}