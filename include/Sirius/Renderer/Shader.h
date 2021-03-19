
#pragma once

#include <glad/glad.h>

#include "srspch.h"

namespace Sirius
{
    class Shader
    {
        private:

            uint32_t rendererId;

        public:

            Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
            virtual ~Shader();

            void bind() const;
            void unbind() const;
    };
}
