
#pragma once

#include <glm.hpp>

#include "VertexArray.h"

namespace Sirius
{
    class RenderCommand
    {
        public:

            static void clear();
            static void setClearColor(const glm::vec4& color);

            static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
    };
}
