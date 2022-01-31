
#pragma once

#include <filesystem>

namespace Sirius
{
    enum class TextureType: uint8_t
    {
        None = 0, Ambient, Diffuse, Specular
    };

    /////////////////////////////////
    /// @brief Abstract texture class
    class Texture
    {
        public:

            uint32_t textureID;
            TextureType type;
            std::filesystem::path path {};
            uint32_t width, height;

            Texture();

            Texture(const std::string& path, const TextureType& type);

            ~Texture() = default;

            virtual void bind(uint32_t slot = 0) const = 0;
    };

    ///////////////////////////
    /// @brief 2D texture class
    class Texture2D: public Texture
    {
        public:

            //////////////////////////////////////////////
            /// @brief Creates a texture with given width
            ///     and height, but no image data
            ///
            /// This is useful when creating a framebuffer
            /// object. The texture has immutable storage.
            Texture2D(uint32_t width, uint32_t height);

            ////////////////////////////////////////////////////////
            /// @brief Creates a new texture from the file at `path`
            ///
            /// The texture has immutable storage.
            Texture2D(const std::string& path, const TextureType& type);

            //////////////////////////////
            /// @brief Deletes the texture
            ~Texture2D();

            /////////////////////////////////////
            /// @brief Bind the texture to OpenGL
            virtual void bind(uint32_t slot = 0) const override;
    };

    enum class CubeFace
    {
        RIGHT = 0, LEFT, TOP, BOTTOM, FRONT, BACK,
        POSX = 0, NEGX, POSY, NEGY, POSZ, NEGZ
    };

    class Texture3D: public Texture
    {
        public:

            Texture3D(const std::unordered_map<CubeFace, std::string>& faces, TextureType type);

            ~Texture3D();

            virtual void bind(uint32_t slot = 0) const override;
    };
}
