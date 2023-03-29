
#pragma once

#include "srspch.hpp"

#include "Math/Math.hpp"

#include "Renderer/Utils/Buffer.hpp"
#include "Renderer/Utils/VertexArray.hpp"
#include "Renderer/Utils/Texture.hpp"

namespace Sirius
{
    class Model
    {
        private:

            /// @brief Helper class: a model is formed of a mesh
            /// or collection of meshes.
            class Mesh
            {
                public:

                    Ref<VertexArray> vertexArray;

                    std::vector<Vertex> vertices;
                    std::vector<uint32_t> indices;
                    std::vector<Ref<Texture2D>> textures;

                    Mesh() = default;

                    /// @brief A mesh is constructed from the vertices,
                    ///     indices and textures
                    ///
                    /// @details A vertex array is created from
                    /// the mesh vertices and indices, but not
                    /// bound.
                    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, std::vector<Ref<Texture2D>>& textures);
            };

        public:

            std::vector<Mesh> meshes;
            fs::path path;

            Model() = default;

            /// @brief Creates a model from a file at `filepath`
            ///
            /// Textures are automatically retrieved. Their
            /// filepaths are expected to be relative to the
            /// model's file.
            explicit Model(const fs::path& filepath);
    };
}
