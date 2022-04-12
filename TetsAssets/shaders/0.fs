#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

uniform sampler2D texture_diffuse1;

void main()
{
    // ambient
    vec3 ambient = vec3(0.1) * texture(texture_diffuse1, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-vec3(-0.5, -1.0, -0.3));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(1.0) * diff * texture(texture_diffuse1, TexCoords).rgb;

    vec3 result = ambient + diffuse;
    FragColor = vec4(result, 1.0);
    //FragColor = texture(texture_diffuse1, TexCoords);
}