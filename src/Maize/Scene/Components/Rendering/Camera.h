#pragma once
#include "Maize/Math/Rect.h"

namespace Maize
{
    struct Camera
    {
        FloatRect viewport = FloatRect(0.0f, 0.0f, 1.0f, 1.0f);
        float zoom = 1.0f;

        Camera() = default;

        Camera(const FloatRect& viewport) : viewport(viewport) { }
    };
} // Maize