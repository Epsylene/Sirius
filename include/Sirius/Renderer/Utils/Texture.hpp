
#pragma once

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
            std::string path;
            uint32_t width, height;

            Texture();
            Texture(const std::string& path, const TextureType& type);

            virtual ~Texture() = default;

            virtual TextureType getType() const;

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
            virtual ~Texture2D() override;

            /////////////////////////////////////
            /// @brief Bind the texture to OpenGL
            virtual void bind(uint32_t slot = 0) const override;
    };

    class Texture3D: public Texture
    {
        public:

            uint32_t width, height;

            Texture3D(const std::array<std::string, 6>& facesTexPaths, TextureType type);

            virtual void bind(uint32_t slot = 0) const override;
    };
}
