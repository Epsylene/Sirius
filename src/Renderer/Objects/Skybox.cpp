
#include "Skybox.hpp"

namespace Sirius
{
    Skybox::Skybox(const std::unordered_map<CubeFace, fs::path>& facesTexPaths):
        texture(facesTexPaths, TextureType::Diffuse), cube()
    {
        Logger::trace(LogChannel::SCENE, "Succesfuly imported skybox");
    }
}