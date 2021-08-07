
#include "Sirius/Renderer/Model.hpp"

#include <tiny_obj_loader.h>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace Sirius
{
    Model::Model(const std::string& filepath)
    {
        tinyobj::ObjReader reader;
        SRS_CORE_ASSERT(reader.ParseFromFile(filepath), "Tiny OBJ reader error :" + reader.Error());

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        for (auto& shape: shapes)
        {
            for (auto& index: shape.mesh.indices)
            {
                Vertex vtx {{ attrib.vertices[3 * index.vertex_index],
                               attrib.vertices[3 * index.vertex_index + 1],
                               attrib.vertices[3 * index.vertex_index + 2] },
                            { attrib.normals[3 * index.normal_index],
                              attrib.normals[3 * index.normal_index + 1],
                              attrib.normals[3 * index.normal_index + 2]},
                            { attrib.texcoords[2 * index.texcoord_index],
                              attrib.texcoords[2 * index.texcoord_index + 1] }};

                if(!attrib.colors.empty())
                {
                    vtx.color = { attrib.colors[3 * index.vertex_index],
                                  attrib.colors[3 * index.vertex_index + 1],
                                  attrib.colors[3 * index.vertex_index + 2] };
                }

                vertices.emplace_back(vtx);
                indices.push_back(indices.size());
            }
        }

        for (auto& mat: materials)
        {
            if(!mat.diffuse_texname.empty() && textures.find(mat.diffuse_texname) == textures.end())
                textures.emplace(mat.diffuse_texname, Texture2D(mat.diffuse_texname, TextureType::Diffuse));

            if(!mat.specular_texname.empty() && textures.find(mat.specular_texname) == textures.end())
                textures.emplace(mat.specular_texname, Texture2D(mat.specular_texname, TextureType::Specular));

            if(!mat.ambient_texname.empty() && textures.find(mat.ambient_texname) == textures.end())
                textures.emplace(mat.ambient_texname, Texture2D(mat.ambient_texname, TextureType::Ambient));
        }
    }

//    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices,
//                std::vector<Texture2D>& textures):
//        vertices(vertices), indices(indices), textures(textures)
//   {}
//
//    Model::Model(const std::string& filepath): path(filepath)
//    {
//        Assimp::Importer importer;
//        const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//        SRS_CORE_ASSERT(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode, "Assimp error : " + std::string(importer.GetErrorString()));
//
//        processNode(scene, scene->mRootNode);
//    }
//
//    void Model::processNode(const aiScene* scene, aiNode* node)
//    {
//        for(unsigned int i = 0; i < node->mNumMeshes; i++)
//        {
//            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//            processMesh(scene, mesh);
//        }
//
//        for(unsigned int i = 0; i < node->mNumChildren; i++)
//        {
//            processNode(scene, node->mChildren[i]);
//        }
//    }
//
//    void Model::processMesh(const aiScene* scene, aiMesh* mesh)
//    {
//        std::vector<Vertex> vertices;
//        std::vector<uint32_t> indices;
//
//        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
//        {
//            Vec2 texCoord {};
//            if(mesh->mTextureCoords[0])
//            {
//                texCoord.x = mesh->mTextureCoords[0][i].x;
//                texCoord.y = mesh->mTextureCoords[0][i].y;
//            }
//
//            vertices.push_back({{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z },
//                                { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z },
//                                texCoord });
//        }
//
//        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
//        {
//            aiFace face = mesh->mFaces[i];
//
//            for(unsigned int j = 0; j < face.mNumIndices; j++)
//                indices.push_back(face.mIndices[j]);
//        }
//
//        if(mesh->mMaterialIndex >= 0)
//        {
//            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//
//            unsigned diffuseTexNb = material->GetTextureCount(aiTextureType_DIFFUSE);
//            unsigned specularTexNb = material->GetTextureCount(aiTextureType_SPECULAR);
//
//            if(texLoaded.size() < diffuseTexNb + specularTexNb)
//            {
//                loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
//                loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
//            }
//        }
//
//        meshes.emplace_back(vertices, indices, texLoaded);
//    }
//
//    void Model::loadMaterialTextures(aiMaterial* mat, aiTextureType aiType,
//                                TextureType type)
//    {
//        for (int i = 0; i < mat->GetTextureCount(aiType); ++i)
//        {
//            aiString texName;
//            mat->GetTexture(aiType, i, &texName);
//
//            std::string texPath = path.substr(0, path.find_last_of('/')) + "/" + texName.C_Str();
////            Log::coreTrace(texPath);
//
//            if(texLoaded.empty())
//                texLoaded.emplace_back(texPath, type);
//
//            bool skip = false;
//            for (auto& tex: texLoaded)
//            {
//                if(texPath == tex.path)
//                {
//                    skip = true;
//                    break;
//                }
//            }
//
//            if(!skip)
//                texLoaded.emplace_back(texPath, type);
//        }
//    }
}