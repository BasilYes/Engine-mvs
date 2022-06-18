#version 330 core
out vec4 FragColor;

flat in vec3 Normal;

void main()
{
    vec3 amb = vec3(0.0, 1.0, 0.0);
    vec3 dif = vec3(1.0, 0.0, 0.0);
    
    // ambient
    //vec3 ambient = vec3(0.3) * amb;

    // diffuse
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(-vec3(-0.5, -1.0, -0.3));
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = vec3(1.0) * diff * dif;

    //vec3 result = ambient + diffuse;
    //FragColor = vec4(result, 1.0);
    FragColor = vec4(Normal, 1.0);
}