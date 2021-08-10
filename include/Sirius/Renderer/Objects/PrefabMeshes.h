
#pragma once

#include "Sirius/Renderer/Objects/Model.hpp"

#include "Sirius/Renderer/Utils/Material.hpp"

namespace Sirius
{
    class Cube: public Model
    {
        public:

            Cube();
            explicit Cube(const Material& mat, bool perFaceTexture = true);
    };
}
