
#include "Sirius/Renderer/Utils/Texture.hpp"

#include "Sirius/Core/Core.hpp"

#include <stb_image.h>
#include <glad/glad.h>

namespace Sirius
{
    // -------------------------  TEXTURE  -------------------------

    TextureType Texture::getType() const
    {
        return type;
    }

    Texture::Texture(const std::string& path, const TextureType& type):
        path(path), type(type)
    {}

    Texture::Texture(): type(TextureType::None)
    {}

    // ------------------------  TEXTURE 2D  ------------------------

    Texture2D::Texture2D(uint32_t width, uint32_t height): Texture()
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &textureID);

        glTextureStorage2D(textureID, 1, GL_RGB8, width, height);
        this->width = width;
        this->height = height;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture2D::Texture2D(const std::string& path, const TextureType& type):
        Texture(path, type)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        this->width = width;
        this->height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if(channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        else if(channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }

        SRS_CORE_ASSERT(internalFormat & dataFormat, "Texture at path \"" + path + "\" : format not supported.");

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Generate and bind the texture to OpenGL.
        glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
        // Tell how many mipmaps levels there are, the internal format
        //  of the texture (that is, how it shall be stored in GPU), its
        //  width and its height.
        glTextureStorage2D(textureID, 1, internalFormat, width, height);

        // Magnification and minification filter, that is, which
        //  algorithms are used to make our texture bigger or smaller.
        glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Specify the texture sub-image that will be used, from some pixel
        //  data the format (memory layout) of which is specified, along
        //  with a type. The pixel data will be converted from 'dataformat'
        //  to 'internalformat' in order to be used by OpenGL.
        glTextureSubImage2D(textureID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &textureID);
    }

    void Texture2D::bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, textureID);
    }

    // ------------------------  TEXTURE 3D  ------------------------

    Texture3D::Texture3D(const std::array<std::string, 6>& facesTexPaths, TextureType type)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, nrChannels;
        for (int i = 0; auto& faceTexPath: facesTexPaths)
        {
            unsigned char *data = stbi_load(faceTexPath.c_str(), &width, &height, &nrChannels, 0);

            if (data)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + (i++), 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            else
                SRS_CORE_ASSERT(false, "Cubemap texture failed to load at path: " + faceTexPath)

            stbi_image_free(data);
        }

        this->width = width;
        this->height = height;

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    void Texture3D::bind(uint32_t slot) const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    }
}