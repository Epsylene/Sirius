
#pragma once

#include "srspch.hpp"
#include "Sirius/Core/Core.hpp"
#include "Sirius/Math/Vector/Vector.hpp"
#include "Sirius/Math/Matrix/Matrix.hpp"
#include "Color.hpp"
#include "Texture.hpp"

#include <glad/glad.h>

namespace Sirius
{
    ///////////////////////////////////////////////////////////
    /// @brief DataType
    ///
    /// This is a helper class, used to build the BufferElement
    /// objects. Each DataType represents an abstract type
    /// (float, int, bool, etc) which is then provided to OpenGL
    /// as a number of bytes.
    ///
    /// @see BufferLayout
    enum class DataType: uint8_t
    {
            None = 0,
            Float, Float2, Float3, Float4,
            Int, Int2, Int3, Int4,
            Mat2, Mat4
    };

    ////////////////////////////////////////////////////
    /// @brief Get the DataType type size in bytes
    static uint32_t dataTypeSize(DataType type)
    {
        switch (type)
        {
            case DataType::Float: return 4;
            case DataType::Float2: return 4 * 2;
            case DataType::Float3: return 4 * 3;
            case DataType::Float4: return 4 * 4;

            case DataType::Int: return 4;
            case DataType::Int2: return 4 * 2;
            case DataType::Int3: return 4 * 3;
            case DataType::Int4: return 4 * 4;

            case DataType::Mat2: return 4 * 2 * 2;
            case DataType::Mat4: return 4 * 4 * 4;

            case DataType::None: break;
        }

        SRS_CORE_ASSERT(false, "Unknown shader data type.")
        return -1;
    }

    static GLenum dataTypeToGLType(DataType type)
    {
        switch (type)
        {
            case DataType::Float: return GL_FLOAT;
            case DataType::Float2: return GL_FLOAT;
            case DataType::Float3: return GL_FLOAT;
            case DataType::Float4: return GL_FLOAT;

            case DataType::Int: return GL_INT;
            case DataType::Int2: return GL_INT;
            case DataType::Int3: return GL_INT;
            case DataType::Int4: return GL_INT;

            case DataType::Mat2: break;
            case DataType::Mat4: break;

            case DataType::None: break;
        }

        SRS_CORE_ASSERT(false, "Unknown shader data type.")
        return -1;
    }

    //////////////////////////////////////////////////////////
    /// @brief OpenGL vertex buffer element abstraction
    ///
    /// This is a helper class, used to build the BufferLayout
    /// objects. Each BufferElement represents a group of tightly
    /// packed, same-type data in the vertex buffer (for example,
    /// a group of four floats or one of three integers).
    ///
    /// @see BufferLayout
    struct BufferElement
    {
        std::string name;
        std::vector<DataType> types;
        uint32_t arrayNb = 1;
        uint32_t offset = 0;
        size_t size;
        bool normalized;

        BufferElement() = default;

        BufferElement(DataType type, const std::string& name, bool normalized = false):
            name(name), types({type}), size(dataTypeSize(type)), normalized(normalized) {}

        ////////////////////////////////////////////////////////
        /// @brief Vertex buffer element constructor
        /// @param types The buffer element types
        /// @param name The buffer element name
        /// @param normalized Normalize fixed-point data values
        ///  (default to false)
        BufferElement(const std::vector<DataType>& types, const std::string& name, size_t arrayNb = 1):
            name(name), types(types), size(0), normalized(false), arrayNb(arrayNb)
        {
            for (auto& type: types)
            {
                size += dataTypeSize(type);
            }

            size *= arrayNb;
        }

        ///////////////////////////////////////////////////////////
        /// @brief Vertex buffer element underlying data type count
        /// @return The number of elements of a certain DataType
        ///  in a vertex buffer element.
        /// @see DataType
        uint32_t count() const
        {
            if(types.size() == 1)
                switch (*types.begin())
                {
                    case DataType::Float: return 1;
                    case DataType::Float2: return 2;
                    case DataType::Float3: return 3;
                    case DataType::Float4: return 4;

                    case DataType::Int: return 1;
                    case DataType::Int2: return 2;
                    case DataType::Int3: return 3;
                    case DataType::Int4: return 4;

                    case DataType::None: break;
                }

            SRS_CORE_ASSERT(false, "Unknown shader or not supported data type.")
            return -1;
        }
    };

    /////////////////////////////////////////////////////////////////
    /// @brief Vertex buffer layout abstraction class
    ///
    /// This class intends allowing to show the vertex buffer layout
    /// in a simple and easy-to-understand fashion, asking to provide
    /// an initializer list of BufferElement objects, which comprise
    /// a DataType and a string with the name of the element
    /// group (for example, "position" or "color").
    ///
    /// @see BufferElement, DataType
    class BufferLayout
    {
        private:

            std::vector<BufferElement> elements;
            uint32_t stride;

        public:

            BufferLayout() = default;

            /////////////////////////////////////////
            /// @brief Get the vertex buffer elements
            inline const std::vector<BufferElement>& getElements() const { return elements; }

            //////////////////////////////////////////////////////////
            /// @brief BufferLayout constructor
            ///
            /// A buffer layout is a list of same-type data groups,
            /// which are given an explanatory name.
            ///
            /// @param elements The list of BufferElement objects
            /// @see BufferElement
            BufferLayout(const std::initializer_list<BufferElement>& elements): elements(elements)
            {
                uint32_t offset = 0;
                stride = 0;

                for (auto& e: this->elements)
                {
                    // Offset is where an element group starts, stride
                    // the distance to the next same element group.
                    e.offset = offset;
                    stride += e.size;
                    offset += e.size;
                }
            }

            ///////////////////////////////////////////////////////
            /// @brief Get the distance between the elements of the
            ///  vertex buffer
            inline uint32_t getStride() const { return stride; }

            std::vector<BufferElement>::iterator begin() { return elements.begin(); }
            std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
            std::vector<BufferElement>::iterator end() { return elements.end(); }
            std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

            size_t size() const { return elements.size(); };
    };

    struct Vertex
    {
        Vec3 pos, normal;
        Vec2 texCoord;
        Color color;

        Vertex(const Vec3& pos, const Vec3& normal, const Vec2& texCoord,
                const Color& color = Color::White):
            pos(pos), normal(normal), texCoord(texCoord), color(color) {}
    };

    ///////////////////////////////////////////
    /// @brief Vertex buffers abstraction class
    class VertexBuffer
    {
        private:

            uint32_t bufferID;
            BufferLayout layout;

        public:

            ///////////////////////////////////////////////////////////
            /// @brief Creates a vertex buffer from an array of floats
            ///
            /// The vertex buffer is created and bound to OpenGL, with
            /// usage set to `GL_STATIC_DRAW` (modified once, drawn
            /// multiple times).
            ///
            /// @param vertices The array of vertices
            /// @param size The array size in bytes (`sizeof()`)
            VertexBuffer(float* vertices, size_t size);

            ///////////////////////////////////////////////////////////
            /// @brief Create a vertex buffer from an array of vertices
            ///
            /// The vertex buffer is created and bound to OpenGL, with
            /// usage set to `GL_STATIC_DRAW` (modified once, drawn
            /// multiple times). Its layout is set to [pos, normal,
            /// texCoords].
            ///
            /// @param vertices The array of vertices
            /// @see Vertex struct
            explicit VertexBuffer(const std::vector<Vertex>& vertices);

            ////////////////////////////////////////////
            /// @brief VertexBuffer destructor
            /// 
            /// Calls glDelete() over the vertex buffer.
            virtual ~VertexBuffer();

            /////////////////////////////////
            /// @brief Bind the vertex buffer
            void bind() const;

            ///////////////////////////////////
            /// @brief Unbind the vertex buffer
            void unbind() const;

            ///////////////////////////////////////
            /// @brief Get the vertex buffer layout
            /// @see BufferLayout
            virtual const BufferLayout& getLayout() const { return layout; }

            ///////////////////////////////////////
            /// @brief Set the vertex buffer layout
            /// @see BufferLayout
            virtual void setLayout(const BufferLayout& layout) { this->layout = layout; }
    };

    //////////////////////////////////////////
    /// @brief Index buffers abstraction class
    class IndexBuffer
    {
        private:

            uint32_t idxBufferID;
            uint32_t count;

        public:

            /////////////////////////////////////////////////////////
            /// @brief Main constructor
            /// 
            /// The index buffer is created and bound to OpenGL, with
            /// usage set to GL_STATIC_DRAW (modified once, drawn 
            /// multiple times).
            ///
            /// @param indices The vertex indices array
            /// @param count The array number of elements
            IndexBuffer(const uint32_t* indices, size_t count);

            explicit IndexBuffer(const std::vector<uint32_t>& indices);

            //////////////////////////////////
            /// @brief Index Buffer destructor
            virtual ~IndexBuffer();

            ////////////////////////////////
            /// @brief Bind the index buffer
            void bind() const;

            //////////////////////////////////
            /// @brief Unbind the index buffer
            void unbind() const;

            //////////////////////////////////////////////////////////////////
            /// @brief Get the index buffer array size (in number of elements)
            inline uint32_t getCount() const { return count; }
    };

    class RenderBuffer
    {
        public:

            uint32_t renderBufferID;

            RenderBuffer(uint32_t width, uint32_t height);

            void bind() const;
    };

    class FrameBuffer
    {
        private:

            uint32_t frameBufferID;
            RenderBuffer depthStencilBuffer;

        public:

            Texture2D colorBuffer;

            FrameBuffer(uint32_t width, uint32_t height);

            ~FrameBuffer();

            void bind() const;

            void unbind() const;
    };

    class UniformBuffer
    {
        private:

            uint32_t uniformBufferID;
            BufferLayout layout;

            std::pair<uint32_t, uint32_t> calculateSizeAndOffset(const std::string& name) const;

        public:

            UniformBuffer(const BufferLayout& layout, uint32_t bindingPoint);

            void bind() const;

            void uploadMat4(const std::string& name, const Mat4& mat);

            void uploadFloat3(const std::string& name, const Vec3& vec);

            void uploadStruct(const std::string& name, const void* data);
    };
}
