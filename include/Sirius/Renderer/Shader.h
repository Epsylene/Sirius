
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

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

            //////////////////////////////////////////////////
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

            ///////////////////////////////////////////////
            /// @brief Upload an int uniform to the shader.
            void uploadUniformInt(const std::string& name, int val);

            ////////////////////////////////////////////////
            /// @brief Upload a float uniform to the shader.
            void uploadUniformFloat(const std::string& name, float val);

            /////////////////////////////////////////////////////////////////////
            /// @brief Upload a 2-dimensional float vector uniform to the shader.
            void uploadUniformFloat2(const std::string& name, const glm::vec2& val);

            /////////////////////////////////////////////////////////////////////
            /// @brief Upload a 3-dimensional float vector uniform to the shader.
            void uploadUniformFloat3(const std::string& name, const glm::vec3& val);

            /////////////////////////////////////////////////////////////////////
            /// @brief Upload a 4-dimensional float vector uniform to the shader.
            void uploadUniformFloat4(const std::string& name, const glm::vec4& val);

            /////////////////////////////////////////////////////////////////////
            /// @brief Upload a 4-dimensional float matrix uniform to the shader.
            void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    };
}
