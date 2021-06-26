
#include "Sirius/Renderer/Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <Sirius/Math/Matrix/Matrix4.h>

#include "Sirius/Core/Core.h"

namespace Sirius
{
    static GLenum shaderTypeFromString(const std::string& type)
    {
        if(type == "vertex") return GL_VERTEX_SHADER;
        if(type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

        SRS_CORE_ASSERT(false, "Unknown shader type !");
    }

    Shader::Shader(const std::string& filepath)
    {
        // Read the source file, extract the shader sources and compile them
        std::string source = readFile(filepath);
        auto shaderSources = preprocess(source);
        compile(shaderSources);

        // Extract the shader's name from the file's name
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;

        this->name = filepath.substr(lastSlash, count);
    }

    Shader::Shader(const std::string& name, const std::string& vertexSrc,
                   const std::string& fragmentSrc): name(name)
    {
        // Compile the shaders from their sources
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(sources);
    }

    Shader::~Shader()
    {
        glDeleteProgram(rendererId);
    }

    std::string Shader::readFile(const std::string& filepath)
    {
        std::string result;
        std::ifstream file(filepath, std::ios::binary);

        if(file)
        {
            // Make 'result' the size of the file string
            file.seekg(0, std::ios::end);
            result.resize(file.tellg());

            // Read the file from the beggining to result.size()
            // (that is, entirely) and place it in 'result'.
            file.seekg(0, std::ios::beg);
            file.read(&result[0], result.size());

            file.close();
        }
        else
        {
            Log::coreError("Could not open file '{0}'", filepath);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> Shader::preprocess(const std::string& source)
    {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* token = "#type";
        size_t tokenLength = strlen(token);
        size_t pos = source.find(token);

        while (pos != std::string::npos)
        {
            // Place the cursor at the "vertex" or "fragment" word
            size_t begin = pos + tokenLength + 1;
            size_t eol = source.find_first_of("\r\n", pos);
            SRS_CORE_ASSERT(eol != std::string::npos, "Error");
            std::string type = source.substr(begin, eol - begin);
            SRS_CORE_ASSERT(shaderTypeFromString(type), "Invalid shader type specified.");

            // Add to the unordered map the [shader type] source at
            // [type]
            size_t typePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(token, typePos);
            shaderSources[shaderTypeFromString(type)] = source.substr(typePos, pos - (typePos == std::string::npos ? source.size() - 1 : typePos));
        }

        return shaderSources;
    }

    void Shader::compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        rendererId = glCreateProgram();

        SRS_CORE_ASSERT(shaderSources.size() <= 2, "Too many shaders.");
        std::array<GLenum, 2> glShaderIDs {};

        // Compile the shaders
        int shaderIndex = 0;
        for (auto&[type, source]: shaderSources)
        {
            GLuint shader = glCreateShader(type);
            const char* source_c_str = source.c_str();

            glShaderSource(shader, 1, &source_c_str, nullptr);
            glCompileShader(shader);

            // Check if the compilation fails
            int isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

            if(isCompiled == GL_FALSE)
            {
                int maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<char> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                Log::coreError("{0}", infoLog.data());
                Log::coreError("{0} shader compilation failure !", type);
                return;
            }

            glAttachShader(rendererId, shader);
            glShaderIDs[shaderIndex++] = shader;
        }

        // Link our rendererId
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

            for (auto& id: glShaderIDs)
                glDeleteShader(id);

            Log::coreError("{0}", infoLog.data());
            Log::coreError("OpenGLShader link failure !");

            return;
        }

        for (auto& id: glShaderIDs)
        {
            // Always detach the shaders after a succesful linkage
            glDetachShader(rendererId, id);
        }
    }

    const std::string& Shader::getName()
    {
        return name;
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
                                     const Vec2& val)
    {
        GLint location = glGetUniformLocation(rendererId, name.c_str());
        glUniform2f(location, val.x, val.y);
    }

    void Shader::uploadUniformFloat3(const std::string& name,
                                     const Vec3& val)
    {
        GLint location = glGetUniformLocation(rendererId, name.c_str());
        glUniform3f(location, val.x, val.y, val.z);
    }

    void Shader::uploadUniformFloat4(const std::string& name, const Vec4& val)
    {
        GLint location = glGetUniformLocation(rendererId, name.c_str());
        glUniform4f(location, val.x, val.y, val.z, val.w);
    }

    void Shader::uploadUniformMat4(const std::string& name, const Mat4& matrix)
    {
        GLint location = glGetUniformLocation(rendererId, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(matrix));
    }

    void ShaderLibrary::add(const std::shared_ptr<Shader>& shader)
    {
        auto& name = shader->getName();

        if(shaders.find(name) != shaders.end())
            Log::coreError("Shader '{0}' already exists !", name);

        shaders[name] = shader;
    }

    void ShaderLibrary::add(const std::string& name,
                            const std::shared_ptr<Shader>& shader)
    {
        if(shaders.find(name) != shaders.end())
            Log::coreError("Shader '{0}' already exists !", name);

        shaders[name] = shader;
    }

    std::shared_ptr<Shader> ShaderLibrary::load(const std::string& filepath)
    {
        auto shader = std::make_shared<Shader>(filepath);
        add(shader);

        return shader;
    }

    std::shared_ptr<Shader>
    ShaderLibrary::load(const std::string& name, const std::string& filepath)
    {
        auto shader = std::make_shared<Shader>(filepath);
        add(name, shader);

        return shader;
    }

    std::shared_ptr<Shader>& ShaderLibrary::get(const std::string& name)
    {
        if(shaders.find(name) == shaders.end())
            Log::coreError("Shader '{0}' not found !", name);

        return shaders[name];
    }
}
