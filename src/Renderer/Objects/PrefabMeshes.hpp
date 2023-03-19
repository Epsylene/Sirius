
#pragma once

#include "Model.hpp"

#include "Renderer/Utils/Material.hpp"

namespace Sirius
{
    class Cube: public Model
    {
        public:

            Cube();

            explicit Cube(const Material& mat, bool perFaceTexture = true);
    };
}
