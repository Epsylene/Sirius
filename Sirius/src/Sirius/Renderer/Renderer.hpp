
#pragma once

#include "srspch.hpp"

#include "Utils/VertexArray.hpp"
#include "Utils/Shader.hpp"
#include "Objects/Model.hpp"
#include "RenderCommand.hpp"

#include "Objects/Camera.hpp"

namespace Sirius
{
    enum PostProcessingFlags
    {
        NONE = 0, INVERSION, GRAYSCALE, EDGES, SHARPEN, BLUR
    };

    struct Kernel
    {
        static const Mat3 Edges;
        static const Mat3 Sharpen;
        static const Mat3 Blur;
    };

    /////////////////////////////////////////////
    /// @brief Global renderer class
    ///
    /// This class provides a number of functions
    /// to initialize and perform tasks common to
    /// the 2D and 3D renderers.
    class Renderer
    {
        private:

            struct SceneData
            {
                Scope<FrameBuffer> renderFBO, postRenderFBO;
                Ref<Shader> postprocess;
                Ref<VertexArray> renderQuad;

                Ref<UniformBuffer> cameraData;
            };

        public:

            static Scope<SceneData> sceneData;

            /////////////////////////////////////////
            /// @brief Initialize the global renderer
            static void init();

            ///////////////////////////////////////
            /// @brief Set the postprocessing flags
            static void setPostProcessing(PostProcessingFlags flags);

            ////////////////////////////////////////////////
            /// @brief Apply the postprocessing to the given
            ///     framebuffer color buffer
            static void applyPostProcessing(const Scope<FrameBuffer>& frameBuffer, const Matrix4f& transform = identity<4>());

            //////////////////////////////////////////////
            /// @brief Performs pre-rendering tasks
            ///
            /// Binds the render FBO, activates the depth
            /// test and sets the wireframe mode and scene
            /// background color.
            static void preRender();

            /////////////////////////////////////////////////
            /// @brief Performs post-rendering tasks
            ///
            /// Applies the postprocessing on the render FBO,
            /// and binds that to the post-render FBO, that
            /// is drawn on the ImGui "Scene" panel.
            static void postRender();
    };
}
