
#pragma once

#include "srspch.h"

#include "Buffer.h"

namespace Sirius
{
    /////////////////////////////////////////
    /// @brief Vertex array abstraction class
    class VertexArray
    {
        private:

            uint32_t rendererId;
            std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
            std::shared_ptr<IndexBuffer> indexBuffer;

        public:

            VertexArray();
            virtual ~VertexArray();

            ////////////////////////////////
            /// @brief Bind the vertex array
            virtual void bind() const;

            //////////////////////////////////
            /// @brief Unbind the vertex array
            virtual void unbind() const;

            //////////////////////////////////////////////////////
            /// @brief Add a vertex buffer
            /// @param vertexBuffer A pointer to the vertex buffer
            virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);

            ///////////////////////////////////////////////////
            /// @brief Set the index buffer
            /// @param indexBuffer A pointer to an index buffer
            virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

            /////////////////////////////////
            /// @brief Get the vertex buffers
            virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return vertexBuffers; }

            ///////////////////////////////
            /// @brief Get the index buffer
            virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return indexBuffer; }
    };
}