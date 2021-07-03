
#pragma once

#include "srspch.hpp"

#include "Buffer.hpp"

namespace Sirius
{
    /////////////////////////////////////////
    /// @brief Vertex array abstraction class
    class VertexArray
    {
        private:

            uint32_t rendererId;
            std::vector<Ref<VertexBuffer>> vertexBuffers;
            Ref<IndexBuffer> indexBuffer;

        public:

            //////////////////////////////////////////
            /// @brief Creates an OpenGL vertex array.
            VertexArray();

            ///////////////////////////////////////////////////////
            /// @brief Creates an OpenGL vertex array from a vertex
            ///     buffer and an index buffer.
            ///
            /// @param vb The vertex buffer
            /// @param ib The index buffer
            VertexArray(const Ref<VertexBuffer>& vb, const Ref<IndexBuffer>& ib);

            //////////////////////////////////////////////
            /// @brief
            /// @param vertices
            /// @param layout
            /// @param indices
            template<unsigned long long s1, unsigned long long s2>
            VertexArray(std::array<float, s1> vertices, const BufferLayout& layout, std::array<uint32_t, s2> indices)
            {
                auto vb = std::make_shared<VertexBuffer>(vertices.data(), sizeof(vertices));
                vb->setLayout(layout);
                addVertexBuffer(vb);

                auto ib = std::make_shared<IndexBuffer>(indices.data(), std::size(indices));
                setIndexBuffer(ib);
            }

            ////////////////////////////////
            /// @brief Bind the vertex array
            void bind() const;

            //////////////////////////////////
            /// @brief Unbind the vertex array
            void unbind() const;

            //////////////////////////////////////////////////////
            /// @brief Add a vertex buffer
            /// @param vertexBuffer A pointer to a vertex buffer
            void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);

            ///////////////////////////////////////////////////
            /// @brief Set the index buffer
            /// @param indexBuffer A pointer to the index buffer
            void setIndexBuffer(
                    const Ref<IndexBuffer>& indexBuffer);

            /////////////////////////////////
            /// @brief Get the vertex buffers
            const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const { return vertexBuffers; }

            ///////////////////////////////
            /// @brief Get the index buffer
            const Ref<IndexBuffer>& getIndexBuffer() const { return indexBuffer; }
    };
}