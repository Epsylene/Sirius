
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

            ////////////////////////////////
            /// @brief Bind the vertex array
            virtual void bind() const;

            //////////////////////////////////
            /// @brief Unbind the vertex array
            virtual void unbind() const;

            //////////////////////////////////////////////////////
            /// @brief Add a vertex buffer
            /// @param vertexBuffer A pointer to a vertex buffer
            virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);

            ///////////////////////////////////////////////////
            /// @brief Set the index buffer
            /// @param indexBuffer A pointer to the index buffer
            virtual void setIndexBuffer(
                    const Ref<IndexBuffer>& indexBuffer);

            /////////////////////////////////
            /// @brief Get the vertex buffers
            virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const { return vertexBuffers; }

            ///////////////////////////////
            /// @brief Get the index buffer
            virtual const Ref<IndexBuffer>& getIndexBuffer() const { return indexBuffer; }
    };
}