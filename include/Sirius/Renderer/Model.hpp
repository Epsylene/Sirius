
#pragma once

#include "Sirius/Math/Vector/Vector.hpp"

#include "Sirius/Renderer/Buffer.hpp"
#include "Sirius/Renderer/VertexArray.hpp"
#include "Sirius/Renderer/Texture.hpp"

#include "srspch.hpp"

#include <assimp/scene.h>

namespace Sirius
{
//    class Mesh
//    {
//        public:
//
//            std::vector<Vertex> vertices;
//            std::vector<uint32_t> indices;
//            std::vector<Texture2D> textures;
//
//            Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, std::vector<Texture2D>& textures);
//    };
//
//    class Model
//    {
//        private:
//
//            std::vector<Texture2D> texLoaded;
//
//            void processNode(const aiScene* scene, aiNode* node);
//            void processMesh(const aiScene* scene, aiMesh* mesh);
//            void loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType type);
//
//        public:
//
//            std::vector<Mesh> meshes;
//            std::string path;
//
//            explicit Model(const std::string& filepath);
//    };

    class Model
    {
        public:

            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;
            std::unordered_map<std::string, Texture2D> textures;

            explicit Model(const std::string& filepath);
    };
}
