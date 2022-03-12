
#pragma once

#include "PrefabMeshes.hpp"

namespace Sirius
{
    class Skybox
    {
        public:

            Cube cube;
            Texture3D texture;

            explicit Skybox(const std::unordered_map<CubeFace, fs::path>& facesTexPaths);
    };
}