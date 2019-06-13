#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "../../shader/Shader.h"
#include "../../utils/utils.h"

using namespace std;

class Model
{
public:
    vector<Texture> textures_loaded;	
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    Model(string const &path, bool gamma = false);

    void Draw(Shader shader, unsigned int depthMap, bool renderShadow);

private:

    void loadModel(string const &path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

    glm::vec3 loadMaterialColor(aiMaterial *mat, const char *pKey, unsigned int type, unsigned int idx, string typeName);

};