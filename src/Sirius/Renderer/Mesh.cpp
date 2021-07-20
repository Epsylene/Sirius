
#include "Sirius/Renderer/Mesh.h"

namespace Sirius
{

    Mesh::Mesh(const std::vector<Vertex>& vertices,
               const std::vector<unsigned int>& indices,
               const std::vector<Texture>& textures):
       vertices(vertices), indices(indices)
    {
    }
}