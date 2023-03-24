
#include "Model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <rapidobj/rapidobj.hpp>

namespace Sirius
{
    Model::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices,
                std::vector<Ref<Texture2D>>& textures):
        vertices(vertices), indices(indices), textures(textures)
   {
        auto vb = std::make_shared<VertexBuffer>(vertices);
        auto ib = std::make_shared<IndexBuffer>(indices);

        vertexArray = std::make_shared<VertexArray>(vb, ib);
   }

    Model::Model(const fs::path& filepath): path(filepath)
    {
        rapidobj::Result result = rapidobj::ParseFile(filepath);
        rapidobj::Triangulate(result);

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Ref<Texture2D>> textures;

        auto vtx_nb = result.attributes.positions.size()/3;
        for (int i = 0; i < vtx_nb; i++)
        {
            auto& pos = result.attributes.positions;
            auto& normals = result.attributes.positions;
            auto& tex = result.attributes.texcoords;

            vertices.push_back({{pos[3*i], pos[3*i+1], pos[3*i+2]},
                                {normals[3*i], normals[3*i+1], normals[3*i+2]},
                                {tex[2*i], tex[2*i+1]}});
        }

        for (auto& shape: result.shapes)
            for (auto& idx: shape.mesh.indices)
                indices.push_back(idx.position_index);

        auto diffuse = filepath.parent_path()/result.materials[0].diffuse_texname;
        auto specular = filepath.parent_path()/result.materials[0].specular_texname;
        textures.emplace_back(std::make_shared<Texture2D>(diffuse, TextureType::Diffuse));
        textures.emplace_back(std::make_shared<Texture2D>(specular, TextureType::Specular));

        meshes.emplace_back(vertices, indices, textures);

        Logger::trace(LogChannel::SCENE, "Succesfuly imported {}", filepath.filename());
    }
}