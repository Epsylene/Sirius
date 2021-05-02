
#pragma once

#include <glad/glad.h>

#include "srspch.h"

namespace Sirius
{
    ///////////////////////////////////
    /// @brief Shader abstraction class
    class Shader
    {
        private:

            uint32_t rendererId;

        public:

            ///////////////////////////
            /// @brief Main constructor
            /// 
            /// @param vertexSrc Vertex shader source code
            /// @param fragmentSrc Fragment shader source code
            Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
            
            ////////////////////////////
            /// @brief Shader destructor
            virtual ~Shader();

            //////////////////////////////////
            /// @brief Bind the shader program
            void bind() const;

            ////////////////////////////////////
            /// @brief Unbind the shader program
            void unbind() const;
    };
}
