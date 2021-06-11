
#pragma once

#include "srspch.h"

#include "VertexArray.h"
#include "Shader.h"

#include "Camera.h"

#include "RenderCommand.h"

namespace Sirius
{
    class Renderer
    {
        private:

            struct SceneData
            {
                glm::mat4 viewProjMatrix;
            };

            static std::unique_ptr<SceneData> sceneData;

        public:

            /////////////////////////////////////////////////////////////
            /// @brief Set up the rendered scene with a particular camera2D
            static void beginScene(Camera& camera);

            /////////////////////////////////
            /// @brief End the rendered scene
            static void endScene();

            ////////////////////////////////////////////////
            /// @brief Submit an object to be rendered
            ///
            /// @param shader The object's shader
            /// @param vertexArray The object's vertex array
            ///
            /// @see Shader and VertexArray classes
            static void submit(std::shared_ptr<Shader>& shader,
                               std::shared_ptr<VertexArray>& vertexArray,
                               const glm::mat4& transform);
    };
}
