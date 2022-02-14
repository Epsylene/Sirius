
#include "Sirius/Renderer/Objects/Model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

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
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filepath.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

        SRS_CORE_ASSERT(scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE), "Assimp error : " + std::string(importer.GetErrorString()));

        if(scene)
            processNode(scene, scene->mRootNode);
    }

    void Model::processNode(const aiScene* scene, aiNode* node)
    {
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(scene, mesh);
        }

        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(scene, node->mChildren[i]);
        }
    }

    void Model::processMesh(const aiScene* scene, aiMesh* mesh)
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vec2 texCoord {};
            if(mesh->mTextureCoords[0])
            {
                texCoord.x = mesh->mTextureCoords[0][i].x;
                texCoord.y = mesh->mTextureCoords[0][i].y;
            }

            vertices.push_back({{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z },
                                { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z },
                                texCoord });
        }

        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        if(mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            unsigned diffuseTexNb = material->GetTextureCount(aiTextureType_DIFFUSE);
            unsigned specularTexNb = material->GetTextureCount(aiTextureType_SPECULAR);

            if(texLoaded.size() < diffuseTexNb + specularTexNb)
            {
                loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
                loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
            }
        }

        meshes.emplace_back(vertices, indices, texLoaded);
    }

    void Model::loadMaterialTextures(aiMaterial* mat, aiTextureType aiType,
                                TextureType type)
    {
        for (int i = 0; i < mat->GetTextureCount(aiType); ++i)
        {
            aiString texName;
            mat->GetTexture(aiType, i, &texName);

            std::string texPath = path.parent_path().generic_string() + "/" + texName.C_Str();

            if(texLoaded.empty())
                texLoaded.emplace_back(std::make_shared<Texture2D>(texPath, type));

            bool skip = false;
            for (auto& tex: texLoaded)
            {
                if(texPath == tex->path)
                {
                    skip = true;
                    break;
                }
            }

            if(!skip)
                texLoaded.emplace_back(std::make_shared<Texture2D>(texPath, type));
        }
    }
}