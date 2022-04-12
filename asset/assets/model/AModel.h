#pragma once
#include <glad/glad.h> 

#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "AMesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class AModel
{
public:
    AModel(string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }
    AModel(unsigned int key) : gammaCorrection(false)
    {
        loadModel("TetsAssets/models/" + to_string(key) + ".obj");
    }
    const std::vector<AMesh>& getMeshes() { return m_meshes; }
private:
    std::vector<Texture> textures_loaded;
    std::vector<AMesh> m_meshes;
    string directory;
    bool gammaCorrection;

    void loadModel(string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    AMesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};