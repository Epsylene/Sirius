
#pragma once

namespace Sirius
{
    /////////////////////////////////
    /// @brief Abstract texture class
    class Texture
    {
        public:

            virtual ~Texture() = default;

            virtual uint32_t getWidth() const = 0;
            virtual uint32_t getHeight() const = 0;

            virtual void bind(uint32_t slot = 0) const = 0;
    };

    ///////////////////////////
    /// @brief 2D texture class
    class Texture2D: public Texture
    {
        private:

            std::string path;
            uint32_t width, height, rendererID;

        public:

            ////////////////////////////////////////////////////////
            /// @brief Creates a new texture from the file at `path`
            explicit Texture2D(const std::string& path);

            //////////////////////////////
            /// @brief Deletes the texture
            virtual ~Texture2D() override;

            ////////////////////////////////////////////
            /// @brief Get the texture's width in pixels
            virtual uint32_t getWidth() const override { return width; };

            /////////////////////////////////////////////
            /// @brief Get the texture's height in pixels
            virtual uint32_t getHeight() const override { return height; };

            /////////////////////////////////////
            /// @brief Bind the texture to OpenGL
            virtual void bind(uint32_t slot = 0) const override;
    };
}
