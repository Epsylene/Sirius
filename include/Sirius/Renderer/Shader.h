
#pragma once

#include <glad/glad.h>

#include "Sirius/Math/Vector/Vector.h"
#include "Sirius/Math/Matrix/Matrix.h"

#include "srspch.h"

namespace Sirius
{
    ///////////////////////////////////
    /// @brief Shader abstraction class
    class Shader
    {
        private:

            uint32_t rendererId;
            std::string name;

            ///////////////////////////////////////////////////
            /// @brief Reads the file in *filepath* and returns
            ///     the result
            std::string readFile(const std::string& filepath);

            /////////////////////////////////////////////////////////
            /// @brief Extracts the shaders sources from the file and
            ///     puts them in an unordered map, which is returned
            std::unordered_map<GLenum, std::string> preprocess(const std::string& source);

            ////////////////////////////////////
            /// @brief Compile the map's shaders
            void compile(const std::unordered_map<GLenum, std::string>& shaderSources);

        public:

            ///////////////////////////////////////////////////////////
            /// @brief Create a shader from the GLSL file at *filepath*
            explicit Shader(const std::string& filepath);

            ////////////////////////////////////////////////////////////
            /// @brief Create a shader from a vertex and fragment source
            /// 
            /// @param vertexSrc Vertex shader source code
            /// @param fragmentSrc Fragment shader source code
            Shader(const std::string& name, const std::string& vertexSrc,
                   const std::string& fragmentSrc);
            
            ////////////////////////////////////////////
            /// @brief Shader destructor
            ///
            /// Calls glDeleteProgram() on 'rendererID`.
            virtual ~Shader();

            ////////////////////////////////
            /// @brief Get the shader's name
            const std::string& getName();

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
            void uploadUniformFloat2(const std::string& name, const Vec2& val);

            /////////////////////////////////////////////////////////////////////
            /// @brief Upload a 3-dimensional float vector uniform to the shader.
            void uploadUniformFloat3(const std::string& name, const Vec3& val);

            /////////////////////////////////////////////////////////////////////
            /// @brief Upload a 4-dimensional float vector uniform to the shader.
            void uploadUniformFloat4(const std::string& name, const Vec4& val);

            /////////////////////////////////////////////////////////////////////
            /// @brief Upload a 4-dimensional float matrix uniform to the shader.
            void uploadUniformMat4(const std::string& name, const Mat4& matrix);
    };

    class ShaderLibrary
    {
        private:

            std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

        public:

            //////////////////////////////////////
            /// @brief Add a shader to the library
            void add(const std::shared_ptr<Shader>& shader);

            ///////////////////////////////////////////////////////
            /// @brief Add shader with a custom name to the library
            void add(const std::string& name, const std::shared_ptr<Shader>& shader);

            /////////////////////////////////////////////////////////////////
            /// @brief Create and add a shader from *filepath* to the library
            std::shared_ptr<Shader> load(const std::string& filepath);

            ////////////////////////////////////////////////////////////////
            /// @brief Create and add a shader from *filepath* with a custom
            ///     name to the library
            std::shared_ptr<Shader> load(const std::string& name, const std::string& filepath);

            ///////////////////////////////////
            /// @brief Get the shader at *name*
            std::shared_ptr<Shader>& get(const std::string& name);
    };
}
