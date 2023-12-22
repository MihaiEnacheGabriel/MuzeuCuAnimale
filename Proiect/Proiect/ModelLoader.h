#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <string>
#include <vector>
#include "Shader.h"

class ModelLoader
{
public:
    ModelLoader(const std::string& modelPath);
    void Render(Shader& shader);

private:
    // Model data
    std::vector<float> vertices; 

    // OpenGL objects
    unsigned int VAO, VBO;

    void SetupMesh();
};

#endif
