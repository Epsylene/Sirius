
#include "RenderCommand.hpp"

#include <glad/glad.h>

namespace Sirius
{
    void RenderCommand::init()
    {
        glEnable(GL_CULL_FACE);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_CLAMP);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void RenderCommand::clear(uint32_t flags)
    {
        glClear(flags);
    }

    void RenderCommand::setClearColor(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RenderCommand::setViewport(uint32_t x, uint32_t y, uint32_t width,
                                    uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void RenderCommand::drawIndexed(const Ref <VertexArray>& vertexArray,
                                    Primitives drawPrimitive)
    {
        glDrawElements((int)drawPrimitive,
                       vertexArray->getIndexBuffer()->getCount(),
                       GL_UNSIGNED_INT,
                       nullptr);

        vertexArray->unbind();
    }

    void RenderCommand::setDepthTest(bool state)
    {
        state ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }

    void RenderCommand::setWireframeMode(bool state)
    {
        state ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
              : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void RenderCommand::setFaceCulling(bool state)
    {
        state ? glEnable(GL_CULL_FACE)
              : glDisable(GL_CULL_FACE);
    }
}