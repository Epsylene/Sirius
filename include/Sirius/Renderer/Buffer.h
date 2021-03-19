
#pragma once

#include <glad/glad.h>

#include "srspch.h"

namespace Sirius
{
    class VertexBuffer
    {
        private:

            uint32_t rendererId;

        public:

            VertexBuffer(float* vertices, size_t size);
            virtual ~VertexBuffer();

            void bind() const;
            void unbind() const;
    };

    class IndexBuffer
    {
        private:

            uint32_t rendererId;
            uint32_t count;

        public:

            IndexBuffer(uint32_t* indices, size_t count);
            virtual ~IndexBuffer();

            void bind() const;
            void unbind() const;

            inline uint32_t getCount() const { return count; }
    };
}
