
#pragma once

#include "Sirius/Renderer/Objects/PrefabMeshes.hpp"

namespace Sirius
{
    class Skybox
    {
        public:

            Cube cube;
            Texture3D texture;

            explicit Skybox(const std::unordered_map<CubeFace, std::string>& facesTexPaths);
    };
}