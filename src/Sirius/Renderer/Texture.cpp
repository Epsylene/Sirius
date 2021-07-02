
#include "Sirius/Renderer/Texture.hpp"

#include "Sirius/Core/Core.hpp"

#include <stb_image.h>
#include <glad/glad.h>

namespace Sirius
{
    Texture2D::Texture2D(const std::string& path): path(path)
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

        SRS_CORE_ASSERT(internalFormat & dataFormat, "Format not supported.");

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Generate and bind the texture to OpenGL.
        glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
        // Tell how many mipmaps levels there are, the internal format
        //  of the texture (that is, how it shall be stored in GPU), its
        //  width and its height.
        glTextureStorage2D(rendererID, 1, internalFormat, width, height);

        // Magnification and minification filter, that is, which
        //  algorithm is used to make our texture bigger or smaller.
        glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Specify the texture sub-image that will be used, from some pixel
        //  data the format (memory layout) of which is specified, along
        //  with a type. The pixel data will be converted from 'dataformat'
        //  to 'internalformat' in order to be used by OpenGL.
        glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &rendererID);
    }

    void Texture2D::bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, rendererID);
    }
}