
#pragma once

#include "Sirius/Core/Core.h"

#include "Camera.h"
#include "Texture.h"

#include "Sirius/Math/Vector/Vector.h"

namespace Sirius
{
    class Renderer2D
    {
        public:

            static void init();
            static void shutdown();

            static void beginScene(const Camera2D& camera);
            static void endScene();

            static void drawQuad(const Vec2& pos, const Vec2& size, const Vec4& color);
            static void drawQuad(const Vec3& pos, const Vec2& size, const Vec4& color);
            static void drawQuad(const Vec2& pos, const Vec2& size, const Ref<Texture2D>& texture);
            static void drawQuad(const Vec3& pos, const Vec2& size, const Ref<Texture2D>& texture);
    };
}
