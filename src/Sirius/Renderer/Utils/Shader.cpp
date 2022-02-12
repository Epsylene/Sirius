
#include "Sirius/Renderer/Utils/Shader.hpp"

namespace Sirius
{
    static GLenum shaderTypeFromString(const std::string& type)
    {
        if(type == "vertex") return GL_VERTEX_SHADER;
        if(type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
        if(type == "geometry") return GL_GEOMETRY_SHADER;

        SRS_CORE_ASSERT(false, "Unknown shader type !");
        return GL_INVALID_ENUM;
    }

    Shader::Shader(const std::filesystem::path& filepath)
    {
        // Read the source file, extract the shader sources and compile them
        std::string source = readFile(filepath);
        auto shaderSources = preprocess(source);
        compile(shaderSources);

        // Extract the shader's name from the file's name
        auto filename = filepath.filename().string();
        this->name = filename.substr(0, filename.find_last_of('.'));
        Log::trace(LogChannel::CORE, name);
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
        glDeleteProgram(shaderID);
    }

    std::filesystem::path path;

    std::string Shader::readFile(const std::filesystem::path& filepath)
    {
        std::string result;
        path = filepath;
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
            Log::error(LogChannel::CORE, "Could not open file '{0}'", filepath.string());
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
        shaderID = glCreateProgram();

        SRS_CORE_ASSERT(shaderSources.size() <= 3, "Too many shaders.");
        std::array<GLenum, 3> glShaderIDs {};

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

                Log::error(LogChannel::CORE, "Shader {} at \"" + path.string() + "\" compilation failure !", type);
                Log::error(LogChannel::CORE, "{}", infoLog.data());
                return;
            }

            glAttachShader(shaderID, shader);
            glShaderIDs[shaderIndex++] = shader;
        }

        // Link our bufferID
        glLinkProgram(shaderID);

        int isLinked = 0;
        glGetProgramiv(shaderID, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            int maxLength = 0;
            glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> infoLog(maxLength);
            glGetProgramInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(shaderID);

            for (auto& id: glShaderIDs)
                glDeleteShader(id);

            Log::error(LogChannel::CORE, "{0}", infoLog.data());
            Log::error(LogChannel::CORE, "OpenGLShader link failure !");

            return;
        }

        for (auto& id: glShaderIDs)
        {
            // Always detach the shaders after a succesful linkage
            glDetachShader(shaderID, id);
        }
    }

    void Shader::bind() const
    {
        glUseProgram(shaderID);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }

    void Shader::uploadUniformBool(const std::string& name, bool val)
    {
        GLint location = glGetUniformLocation(shaderID, name.c_str());
        glUniform1i(location, (int)val);
    }

    void Shader::uploadUniformUint(const std::string& name, uint32_t val)
    {
        GLint location = glGetUniformLocation(shaderID, name.c_str());
        glUniform1ui(location, val);
    }

    void Shader::uploadUniformInt(const std::string& name, int val)
    {
        GLint location = glGetUniformLocation(shaderID, name.c_str());
        glUniform1i(location, val);
    }

    void Shader::uploadUniformFloat(const std::string& name, float val)
    {
        GLint location = glGetUniformLocation(shaderID, name.c_str());
        glUniform1f(location, val);
    }

    void Shader::uploadUniformFloat2(const std::string& name,
                                     const Vec2& val)
    {
        GLint location = glGetUniformLocation(shaderID, name.c_str());
        glUniform2f(location, val.x, val.y);
    }

    void Shader::uploadUniformFloat3(const std::string& name, const Vec3& val)
    {
        GLint location = glGetUniformLocation(shaderID, name.c_str());
        glUniform3f(location, val.x, val.y, val.z);
    }

    void Shader::uploadUniformFloat4(const std::string& name, const Vec4& val)
    {
        GLint location = glGetUniformLocation(shaderID, name.c_str());
        glUniform4f(location, val.x, val.y, val.z, val.w);
    }

    void Shader::uploadUniformMat3(const std::string& name, const Mat3& matrix)
    {
        GLint location = glGetUniformLocation(shaderID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
    }

    void Shader::uploadUniformMat4(const std::string& name, const Mat4& matrix)
    {
        GLint location = glGetUniformLocation(shaderID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    }

    void ShaderLibrary::add(const Ref<Shader>& shader)
    {
        auto& name = shader->name;

        if(shaders.find(name) != shaders.end())
            Log::error(LogChannel::CORE, "Shader '{0}' already exists !", name);

        shaders[name] = shader;
    }

    void ShaderLibrary::add(const std::string& name,
                            const Ref<Shader>& shader)
    {
        if(shaders.find(name) != shaders.end())
            Log::error(LogChannel::CORE, "Shader '{0}' already exists !", name);

        shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::filesystem::path& filepath)
    {
        auto shader = std::make_shared<Shader>(filepath);
        add(shader);

        return shader;
    }

    Ref<Shader>
    ShaderLibrary::load(const std::string& name, const std::filesystem::path& filepath)
    {
        auto shader = std::make_shared<Shader>(filepath);
        add(name, shader);

        return shader;
    }

    Ref <Shader>& ShaderLibrary::operator[](const std::string& name)
    {
        if(shaders.find(name) == shaders.end())
            Log::error(LogChannel::CORE, "Shader '{0}' not found !", name);

        return shaders[name];
    }
}
