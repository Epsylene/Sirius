
#include "Skybox.hpp"

namespace Sirius
{
    Skybox::Skybox(const std::unordered_map<CubeFace, std::string>& facesTexPaths):
        texture(facesTexPaths, TextureType::Diffuse), cube()
    {
    }
}