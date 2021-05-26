
#pragma once

#include "srspch.h"
#include "Sirius/Core.h"

#include <glad/glad.h>

namespace Sirius
{
    ///////////////////////////////////////////////////////////
    /// @brief ShaderDataType
    ///
    /// This is a helper class, used to build the BufferElement
    /// objects. Each ShaderDataType represents an abstract type
    /// (float, int, bool, etc) which is then provided to OpenGL
    /// as a number of bytes.
    ///
    /// @see BufferLayout
    enum class ShaderDataType: uint8_t
    {
            None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4
    };

    ////////////////////////////////////////////////////
    /// @brief Get the ShaderDataType type size in bytes
    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float: return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;

            case ShaderDataType::Int: return 4;
            case ShaderDataType::Int2: return 4 * 2;
            case ShaderDataType::Int3: return 4 * 3;
            case ShaderDataType::Int4: return 4 * 4;

            case ShaderDataType::None: break;
        }

        SRS_CORE_ASSERT(false, "Unknown shader data type.")
        return -1;
    }

    static GLenum shaderTypeToGLType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float: return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;

            case ShaderDataType::Int: return GL_INT;
            case ShaderDataType::Int2: return GL_INT;
            case ShaderDataType::Int3: return GL_INT;
            case ShaderDataType::Int4: return GL_INT;

            case ShaderDataType::None: break;
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
        ShaderDataType type;
        uint32_t offset;
        size_t size;
        bool normalized;

        BufferElement() = default;

        ////////////////////////////////////////////////////////
        /// @brief Vertex buffer element constructor
        /// @param type The buffer element type
        /// @param name The buffer element name
        /// @param normalized Normalize fixed-point data values
        ///  (default to false)
        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false): name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {}

        ///////////////////////////////////////////////////////////
        /// @brief Vertex buffer element underlying data type count
        /// @return The number of elements of a certain ShaderDataType
        ///  in a vertex buffer element.
        /// @see ShaderDataType
        uint32_t count() const
        {
            switch (type)
            {
                case ShaderDataType::Float: return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;

                case ShaderDataType::Int: return 1;
                case ShaderDataType::Int2: return 2;
                case ShaderDataType::Int3: return 3;
                case ShaderDataType::Int4: return 4;

                case ShaderDataType::None: break;
            }

            SRS_CORE_ASSERT(false, "Unknown shader data type.")
            return -1;
        }
    };

    /////////////////////////////////////////////////////////////////
    /// @brief Vertex buffer layout abstraction class
    ///
    /// This class intends allowing to show the vertex buffer layout
    /// in a simple and easy-to-understand fashion, asking to provide
    /// an initializer list of BufferElement objects, which comprise
    /// a ShaderDataType and a string with the name of the element
    /// group (for example, "position" or "color").
    ///
    /// @see BufferElement, ShaderDataType
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
    };

    ///////////////////////////////////////////
    /// @brief Vertex buffers abstraction class
    class VertexBuffer
    {
        private:

            uint32_t rendererId;
            BufferLayout layout;

        public:

            ///////////////////////////////////////////////////////////
            /// @brief Main constructor
            ///
            /// The vertex buffer are created and bound to OpenGL, with
            /// usage set to `GL_STATIC_DRAW` (modified once, drawn
            /// multiple times).
            ///
            /// @param vertices The vertices array
            /// @param size The array size in bytes (`sizeof()`)
            VertexBuffer(float* vertices, size_t size);

            /////////////////////////////////////////
            /// @brief Vertex Buffer destructor
            /// 
            /// Deletes the vertex buffers. 
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

            uint32_t rendererId;
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
            IndexBuffer(uint32_t* indices, size_t count);

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
}
