#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

flat out vec3 Normal;

uniform mat4 viewModel;

void main()
{
    Normal = aNormal;
    gl_Position = viewModel * vec4(aPos, 1.0);
}