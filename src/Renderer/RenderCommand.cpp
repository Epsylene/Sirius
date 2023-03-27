
#include "RenderCommand.hpp"

#include "glad/glad.h"

namespace Sirius
{
    void RenderCommand::init()
    {
        // Enable face culling
        glEnable(GL_CULL_FACE);

        // Enable the Z buffer depth test (which renders objects
        // depending on a depth test function) with depth test
        // GL_LEQUAL (closer objects rendered on top)
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        // Enable depth clamping, which turns off clipping
        // against the near and far planes (objects closer than
        // the near plane or farther than the far plane are
        // clamped to those, so that no "insides" are shown
        // incorrectly)
        glEnable(GL_DEPTH_CLAMP);

        // Enable stencil testing, a buffer which allows writing
        // only to parts of the image, and tell it to keep the
        // buffer values if the stencil or depth test fail, but
        // replace them if both pass.
        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        // Enable blending, a technique to implement
        // transparency, and tell OpenGL to use the
        // source alpha and its complement as factors
        // when blending two colors together.
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