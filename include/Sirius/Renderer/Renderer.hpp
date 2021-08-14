
#pragma once

#include "srspch.hpp"

#include "Sirius/Renderer/Utils/VertexArray.hpp"
#include "Sirius/Renderer/Utils/Shader.hpp"
#include "Sirius/Renderer/Objects/Model.hpp"
#include "Sirius/Renderer/RenderCommand.hpp"

#include "Sirius/Renderer/Objects/Camera.hpp"

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
    /// to initialize and perform common tasks to
    /// the 2D and 3D renderers.
    class Renderer
    {
        private:

            struct SceneData
            {
                Scope<FrameBuffer> preRenderFBO, postRenderFBO;
                Ref<Shader> postprocess;
                Ref<VertexArray> quad;
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

            static void preRender();

            static void postRender();
    };
}
