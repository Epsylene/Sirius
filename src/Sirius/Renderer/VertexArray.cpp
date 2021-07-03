
#include "Sirius/Renderer/VertexArray.hpp"

namespace Sirius
{
    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &rendererId);
    }

    VertexArray::VertexArray(const Ref<VertexBuffer>& vb, const Ref<IndexBuffer>& ib)
    {
        glCreateVertexArrays(1, &rendererId);

        addVertexBuffer(vb);
        setIndexBuffer(ib);
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(rendererId);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(rendererId);
        vertexBuffer->bind();

        SRS_CORE_ASSERT(!vertexBuffer->getLayout().getElements().empty(), "Vertex buffer has no layout.")

        // For each element in the layout, enable the vertex attribute
        // array at the element's index and give it the data it wants
        uint32_t index = 0;
        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element: layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.count(),
                                  shaderTypeToGLType(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.getStride(),
                                  (const void*)element.offset);
            index++;
        }

        vertexBuffers.push_back(vertexBuffer);
    }

    void VertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(rendererId);
        indexBuffer->bind();

        this->indexBuffer = indexBuffer;
    }
}