
#include "Sirius/Renderer/Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include "Sirius/Core/Core.h"

namespace Sirius
{
    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        //------- Vertex shader -------//

        // Create the shader, send to OpenGL and compile it
        unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const char* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, nullptr);

        glCompileShader(vertexShader);
        int isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

        // Check whether compilation was succesful or not
        if(isCompiled == GL_FALSE)
        {
            int maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(vertexShader);

            SRS_CORE_ERROR("{0}", infoLog.data());
            SRS_CORE_ASSERT(false, "Vertex shader compilation failure !")

            return;
        }

        //------- Fragment shader -------//

        unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            int maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            return;
        }

        rendererId = glCreateProgram();

        // Attach the shaders and link the program
        glAttachShader(rendererId, vertexShader);
        glAttachShader(rendererId, fragmentShader);

        glLinkProgram(rendererId);

        int isLinked = 0;
        glGetProgramiv(rendererId, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            int maxLength = 0;
            glGetProgramiv(rendererId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> infoLog(maxLength);
            glGetProgramInfoLog(rendererId, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(rendererId);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            SRS_CORE_ERROR("{0}", infoLog.data());
            SRS_CORE_ASSERT(false, "Shader link failure !")

            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(rendererId, vertexShader);
        glDetachShader(rendererId, fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(rendererId);
    }

    void Shader::bind() const
    {
        glUseProgram(rendererId);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }

    void Shader::uploadUniformInt(const std::string& name, int val)
    {
        GLint location = glGetUniformLocation(rendererId, name.c_str());
        glUniform1i(location, val);
    }

    void Shader::uploadUniformFloat(const std::string& name, float val)
    {
        GLint location = glGetUniformLocation(rendererId, name.c_str());
        glUniform1f(location, val);
    }

    void Shader::uploadUniformFloat2(const std::string& name,
                                           const glm::vec2& val)
    {
        GLint location = glGetUniformLocation(rendererId, name.c_str());
        glUniform2f(location, val.x, val.y);
    }

    void Shader::uploadUniformFloat3(const std::string& name,
                                           const glm::vec3& val)
    {
        GLint location = glGetUniformLocation(rendererId, name.c_str());
        glUniform3f(location, val.x, val.y, val.z);
    }

    void Shader::uploadUniformFloat4(const std::string& name, const glm::vec4& val)
    {
        GLint location = glGetUniformLocation(rendererId, name.c_str());
        glUniform4f(location, val.x, val.y, val.z, val.w);
    }

    void Shader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        GLint location = glGetUniformLocation(rendererId, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
