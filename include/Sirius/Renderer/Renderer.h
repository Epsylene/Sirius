
#pragma once

#include "VertexArray.h"
#include "Shader.h"

#include "RenderCommand.h"

namespace Sirius
{
    class Renderer
    {
        public:

            static void beginScene();
            static void endScene();

            static void submit(std::shared_ptr<Shader>& shader,
                               std::shared_ptr<VertexArray>& vertexArray);
    };
}
