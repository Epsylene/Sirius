
#include "Sirius/Renderer/Utils/Buffer.hpp"

namespace Sirius
{
    //----------- VERTEX BUFFER -----------//

    VertexBuffer::VertexBuffer(float* vertices, size_t size)
    {
        glCreateBuffers(1, &bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
    {
        glCreateBuffers(1, &bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        layout = {{{DataType::Float3, "a_pos"},
                   {DataType::Float3, "a_normal"},
                   {DataType::Float2, "a_texCoord"},
                   {DataType::Float4, "a_vtxColor"}}};
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &bufferID);
    }

    void VertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    }

    void VertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    //----------- INDEX BUFFER -----------//

    IndexBuffer::IndexBuffer(const uint32_t* indices, size_t count): count(count)
    {
        glCreateBuffers(1, &idxBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::IndexBuffer(const std::vector<uint32_t>& indices): count(indices.size())
    {
        glCreateBuffers(1, &idxBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &idxBufferID);
    }

    void IndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBufferID);
    }

    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    //----------- RENDER BUFFER -----------//

    RenderBuffer::RenderBuffer(uint32_t width, uint32_t height)
    {
        glGenRenderbuffers(1, &renderBufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    }

    void RenderBuffer::bind() const
    {
        glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
    }

    //----------- FRAME BUFFER -----------//

    FrameBuffer::FrameBuffer(uint32_t width, uint32_t height): colorBuffer(width, height), depthStencilBuffer(width, height)
    {
        glGenFramebuffers(1, &frameBufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer.textureID, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilBuffer.renderBufferID);

        SRS_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "OpenGL error : framebuffer is not complete.");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteBuffers(1, &frameBufferID);
    }

    void FrameBuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
    }

    void FrameBuffer::unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    //----------- UNIFORM BUFFER -----------//

    UniformBuffer::UniformBuffer(const BufferLayout& layout, uint32_t bindingPoint):
        layout(layout)
    {
        auto offset = 0;
        for (auto& elem: this->layout)
        {
            elem.size = 0;

            for (auto& type: elem.types)
            {
                if(type == DataType::Float3)
                    type = DataType::Float4;

                elem.size += dataTypeSize(type);
            }

            elem.size *= elem.arrayNb;

            elem.offset = offset;
            offset += elem.size;
        }

        glGenBuffers(1, &uniformBufferID);
        glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferID);

        uint32_t allocBytes = 0;
        for (auto& elem: this->layout)
            allocBytes += elem.size;

        glBufferData(GL_UNIFORM_BUFFER, allocBytes, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, uniformBufferID, 0, allocBytes);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UniformBuffer::bind() const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferID);
    }

    std::pair<uint32_t, uint32_t> UniformBuffer::calculateSizeAndOffset(const std::string& name) const
    {
        for (auto& elem: layout)
            if(name == elem.name)
                return {elem.size, elem.offset};

        SRS_CORE_ASSERT(false, "\"" + name + "\" is not an element of the UBO with ID " + std::to_string(uniformBufferID) + ".");
        return {-1, -1};
    }

    void UniformBuffer::uploadMat4(const std::string& name, const Mat4& val)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferID);
        auto [size, offset] = calculateSizeAndOffset(name);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, &val[0][0]);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UniformBuffer::uploadFloat3(const std::string& name, const Vec3& val)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferID);
        auto [size, offset] = calculateSizeAndOffset(name);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, &val.x);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UniformBuffer::uploadStruct(const std::string& name, const void* data, size_t number)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferID);
        auto [size, offset] = calculateSizeAndOffset(name);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size * number, data);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
}
