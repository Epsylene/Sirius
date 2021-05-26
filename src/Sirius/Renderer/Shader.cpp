
#include "Sirius/Renderer/Shader.h"

#include "Sirius/Core.h"

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
}
