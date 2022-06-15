#pragma once
#include "asset/assets/AShader.h"

#include <string>
#include <vector>

struct Vertex 
{
    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;
    vec3 Tangent;
    vec3 Bitangent;
};

struct Texture 
{
    unsigned int id;
    std::string type;
    std::string path;
};

class AMesh
{
public:
    AMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~AMesh();
    void Draw(AShader& shader) const;
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};