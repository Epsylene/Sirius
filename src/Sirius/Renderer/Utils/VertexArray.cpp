
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

        for (auto& vb: vertexBuffers)
        {
            for (int i = 0; i < vb->getLayout().size(); ++i)
            {
                glEnableVertexAttribArray(i);
            }
        }
    }

    void VertexArray::unbind() const
    {
        for (auto& vb: vertexBuffers)
        {
            for (int i = 0; i < vb->getLayout().size(); ++i)
            {
                glDisableVertexAttribArray(i);
            }
        }

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
                                  dataTypeToGLType(*element.types.begin()),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.getStride(),
                                  (const void*)element.offset);
            index++;
        }

        vertexBuffers.push_back(vertexBuffer);

        for (int i = 0; i < layout.size(); ++i)
        {
            glDisableVertexAttribArray(i);
        }
    }

    void VertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        this->bind();
        indexBuffer->bind();

        this->indexBuffer = indexBuffer;
        this->unbind();
    }
}