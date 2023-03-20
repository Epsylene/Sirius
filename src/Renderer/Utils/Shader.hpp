
#pragma once

#include "Math/Math.hpp"
#include "Texture.hpp"

#include "srspch.hpp"
#include "Core/Core.hpp"

#include "glad/glad.h"

namespace Sirius
{
    /// @brief Shader abstraction class
    class Shader
    {
        private:

            uint32_t shaderID;

            /// @brief Reads the file in `filepath` and returns
            ///     the result
            std::string readFile(const fs::path& filepath);

            /// @brief Extracts the shaders sources from the file and
            ///     puts them in an unordered map, which is returned
            std::unordered_map<GLenum, std::string> preprocess(const std::string& source);

            /// @brief Compile the map's shaders
            void compile(const std::unordered_map<GLenum, std::string>& shaderSources);

        public:

            std::string name;

            /// @brief Create a shader from the GLSL file at
            /// `filepath`
            explicit Shader(const fs::path& filepath);

            /// @brief Create a shader from a vertex and
            /// fragment source
            /// 
            /// @param vertexSrc Vertex shader source code
            /// @param fragmentSrc Fragment shader source code
            Shader(const std::string& name, const std::string& vertexSrc,
                   const std::string& fragmentSrc);
            
            /// @brief Shader destructor
            ///
            /// @details Calls glDeleteProgram() on 'textureID`.
            virtual ~Shader();

            void bind() const;
            void unbind() const;

            void uploadUniformBool(const std::string& name, bool val);
            void uploadUniformUint(const std::string& name, uint32_t val);
            void uploadUniformInt(const std::string& name, int val);
            void uploadUniformFloat(const std::string& name, float val);
            void uploadUniformFloat2(const std::string& name, const Vec2& val);
            void uploadUniformFloat3(const std::string& name, const Vec3& val);
            void uploadUniformFloat4(const std::string& name, const Vec4& val);
            void uploadUniformMat3(const std::string& name, const Mat3& matrix);
            void uploadUniformMat4(const std::string& name, const Mat4& matrix);
    };

    class ShaderLibrary
    {
        private:

            std::unordered_map<std::string, Ref<Shader>> shaders;

        public:

            /// @brief Add an existing shader to the library
            void add(const Ref<Shader>& shader);

            /// @brief Add an existing shader with a custom name
            /// to the library
            void add(const std::string& name, const Ref<Shader>& shader);

            /// @brief Create and add a shader from `filepath`
            /// to the library
            Ref<Shader> load(const fs::path& filepath);

            /// @brief Create and add a shader from `filepath`
            /// with a custom name to the library
            Ref<Shader> load(const std::string& name, const fs::path& filepath);

            /// @brief Get a reference to the shader `name`
            Ref<Shader>& operator[](const std::string& name);

            std::unordered_map<std::string, Ref<Shader>>::iterator begin() { return shaders.begin(); }
            std::unordered_map<std::string, Ref<Shader>>::iterator end() { return shaders.end(); }
    };
}
