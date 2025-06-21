#include "Model.hpp"

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include "Macros.hpp"

namespace Core {
    Model::Model(const std::string& path)
    {
        LoadModel(path);
    }

    void Model::Draw(const Shader &shader, const std::vector<std::function<void(const Shader &)>> &setFunctions, bool bindShader) const
    {
        if (bindShader)
        {
            shader.Use();
        }
        for (auto &mesh : _meshes)
        {
            mesh->DrawInstanced(shader, setFunctions, { glm::mat4(1.0f) }, { glm::vec4(1.0f) }, false);
        }
    }

    void Model::DrawInstanced(const Shader& shader,
                              const std::vector<std::function<void(const Shader&)>>& setFunctions,
                              const std::vector<glm::mat4>& models,
                              const std::vector<glm::vec4>& colors,
                              const bool bindShader) const
    {
        ZA_ASSERT(models.size() == colors.size(), "Models and colors size mismatch");

        if (bindShader)
        {
            shader.Use();
        }

        for (auto& mesh : _meshes)
        {
            mesh->DrawInstanced(shader, setFunctions, models, colors, false);
        }
    }

    void Model::LoadModel(const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        ProcessNode(scene->mRootNode, scene);
    }

    void Model::ProcessNode(aiNode* node, const aiScene* scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            _meshes.push_back(ProcessMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        return std::make_shared<Mesh>(vertices, indices);
    }


}
