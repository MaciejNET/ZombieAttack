#ifndef MODEL_HPP
#define MODEL_HPP
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.hpp"
#include <memory>
#include <glm/glm.hpp>

namespace Core {
    class Model
    {
    public:
        explicit Model(const std::string& path);
        void Draw(const Shader& shader, const std::vector<std::function<void(const Shader&)>>& setFunctions, bool bindShader = true) const;
        void DrawInstanced(const Shader& shader,
                           const std::vector<std::function<void(const Shader&)>>& setFunctions,
                           const std::vector<glm::mat4>& models,
                           const std::vector<glm::vec4>& colors,
                           bool bindShader = true) const;
        std::vector<std::shared_ptr<Mesh>> GetMeshes() const { return _meshes; }
    private:
        std::vector<std::shared_ptr<Mesh>> _meshes;
        void LoadModel(const std::string& path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
    };
}

#endif //MODEL_HPP
