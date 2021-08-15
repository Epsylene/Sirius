
#pragma once

#include "Sirius/Renderer/Objects/PrefabMeshes.h"

namespace Sirius
{
    class Skybox
    {
        public:

            Cube cube;
            Texture3D texture;

            explicit Skybox(const std::array<std::string, 6>& facesTexPaths);
    };
}