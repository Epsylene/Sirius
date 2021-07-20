
#pragma once

#include "Sirius/Math/Vector/Vector.hpp"

#include "Sirius/Renderer/Texture.hpp"
#include "Sirius/Renderer/VertexArray.hpp"

namespace Sirius
{
    struct Vertex
    {
        Vec3 pos, normal, texCoords;
    };

    class Mesh
    {
        private:

            VertexArray vertexArray;

        public:

            std::vector<Vertex> vertices;
            std::vector<unsigned> indices;
            std::vector<Texture> textures;

            Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, const std::vector<Texture>& textures);
    };
}
