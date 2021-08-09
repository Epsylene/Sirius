
#pragma once

#include "srspch.hpp"

#include "Sirius/Math/Vector/Vector.hpp"

#include "Sirius/Renderer/Utils/Buffer.hpp"
#include "Sirius/Renderer/Utils/VertexArray.hpp"
#include "Sirius/Renderer/Utils/Texture.hpp"

#include <assimp/scene.h>

namespace Sirius
{
    class Mesh
    {
        public:

            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;
            std::vector<Texture2D> textures;

            Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, std::vector<Texture2D>& textures);
    };

    class Model
    {
        private:

            std::vector<Texture2D> texLoaded;

            void processNode(const aiScene* scene, aiNode* node);
            void processMesh(const aiScene* scene, aiMesh* mesh);
            void loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType type);

        public:

            std::vector<Mesh> meshes;
            std::string path;

            explicit Model(const std::string& filepath);
    };
}
