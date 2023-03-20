
#pragma once

#include "srspch.hpp"

#include "Buffer.hpp"

namespace Sirius
{
    /// @brief Vertex array abstraction class
    class VertexArray
    {
        private:

            std::vector<Ref<VertexBuffer>> vertexBuffers;
            Ref<IndexBuffer> indexBuffer;

        public:
            uint32_t vtxArrID;

            /// @brief Creates an OpenGL vertex array.
            VertexArray();

            /// @brief Creates an OpenGL vertex array from a vertex
            ///     buffer and an index buffer.
            VertexArray(const Ref<VertexBuffer>& vb, const Ref<IndexBuffer>& ib);

            void bind() const;
            void unbind() const;

            void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
            void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer);
            const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const { return vertexBuffers; }
            const Ref<IndexBuffer>& getIndexBuffer() const { return indexBuffer; }
    };
}