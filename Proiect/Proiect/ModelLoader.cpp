//#include "ModelLoader.h"
////#include <assimp/Importer.hpp>
////#include <assimp/scene.h>
////#include <assimp/postprocess.h>
//#include <iostream>
//
//ModelLoader::ModelLoader(const std::string& modelPath)
//{
//    Assimp::Importer importer;
//    const aiScene* scene = importer.ReadFile(modelPath,
//        aiProcess_Triangulate |
//        aiProcess_FlipUVs |
//        aiProcess_CalcTangentSpace);
//
//    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//    {
//        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
//        return;
//    }
//
//    // TODO: Process the loaded data stored in 'scene'
//    // This might involve iterating over the meshes in the scene and extracting the vertices, normals, texture coordinates, etc.
//    // You would then store this data in 'vertices' and other member variables.
//
//    SetupMesh();
//}
//
//void ModelLoader::SetupMesh()
//{
//    // Generate and bind VAO and VBO
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    // Load your vertex data into the VBO
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
//
//    // Specify the layout of the vertex data
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // Unbind the VBO and VAO
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//void ModelLoader::Render(Shader& shader)
//{
//    // Use shader program
//    shader.Use();
//
//    // Bind VAO
//    glBindVertexArray(VAO);
//
//    // Make draw call
//    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
//
//    // Unbind the VAO
//    glBindVertexArray(0);
//}
