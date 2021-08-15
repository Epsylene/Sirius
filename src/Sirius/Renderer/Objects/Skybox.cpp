
#include "Sirius/Renderer/Objects/Skybox.hpp"

namespace Sirius
{
    Skybox::Skybox(const std::array<std::string, 6>& facesTexPaths):
        texture(facesTexPaths, TextureType::Diffuse), cube()
    {
    }
}