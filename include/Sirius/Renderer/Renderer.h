
#pragma once

#include "srspch.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "Camera.h"

namespace Sirius
{
    ////////////////////////////////
    /// @brief Global renderer class
    class Renderer
    {
        private:

            struct SceneData
            {
                Mat4 viewProjMatrix;
            };

            static std::unique_ptr<SceneData> sceneData;

        public:

            /////////////////////////////////////////
            /// @brief Initialize the global renderer
            static void init();

            ///////////////////////////////////////////////////////////////
            /// @brief Set up the rendered scene with a particular camera2D
            static void beginScene(Camera& camera);

            /////////////////////////////////
            /// @brief End the rendered scene
            static void endScene();

            ////////////////////////////////////////////////////
            /// @brief Window resize renderer callback
            ///
            /// The renderer viewport's width and height are set
            /// to match the resized window's.
            ///
            /// @param width The resized window's width
            /// @param height The resized window's height
            static void onWindowResize(uint32_t width, uint32_t height);

            ////////////////////////////////////////////////////////
            /// @brief Submit an object to be rendered
            ///
            /// @param shader The object's shader
            /// @param vertexArray The object's vertex array
            /// @param transform The transform applied to the object
            ///
            /// @see Shader and VertexArray classes
            static void submit(const Ref<Shader>& shader,
                               const Ref<VertexArray>& vertexArray,
                               const Mat4& transform = identity<4>());
    };
}
