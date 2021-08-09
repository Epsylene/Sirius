
#include "Sirius/Renderer/Utils/VertexArray.hpp"

namespace Sirius
{
    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &vtxArrID);
    }

    VertexArray::VertexArray(const Ref<VertexBuffer>& vb, const Ref<IndexBuffer>& ib)
    {
        glCreateVertexArrays(1, &vtxArrID);

        addVertexBuffer(vb);
        setIndexBuffer(ib);
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(vtxArrID);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(vtxArrID);
        vertexBuffer->bind();

        SRS_CORE_ASSERT(!vertexBuffer->getLayout().getElements().empty(), "Vertex buffer has no layout.")

        // For each element in the layout, enable the vertex attribute
        // array at the element's index and give it the data it wants
        const auto& layout = vertexBuffer->getLayout();
        for (uint32_t index = 0; const auto& element: layout)
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
        glBindVertexArray(vtxArrID);
        indexBuffer->bind();

        this->indexBuffer = indexBuffer;
    }
}