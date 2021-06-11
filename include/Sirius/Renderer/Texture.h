
#pragma once

namespace Sirius
{
    class Texture
    {
        public:

            virtual ~Texture() = default;

            virtual uint32_t getWidth() const = 0;
            virtual uint32_t getHeight() const = 0;

            virtual void bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D: public Texture
    {
        private:

            std::string path;
            uint32_t width, height, rendererID;

        public:

            explicit Texture2D(const std::string& path);
            virtual ~Texture2D() override;

            virtual uint32_t getWidth() const override { return width; };
            virtual uint32_t getHeight() const override { return height; };

            virtual void bind(uint32_t slot = 0) const override;
    };
}
