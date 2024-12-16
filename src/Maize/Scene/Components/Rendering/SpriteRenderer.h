#pragma once

#include "Maize/Math/Rect.h"
#include "Maize/Math/Vec2.h"
#include "Maize/Rendering/Sprite.h"

namespace Maize
{
    struct SpriteRenderer
    {
        Sprite sprite;

        SpriteRenderer() = default;

        SpriteRenderer(const Sprite& sprite) : sprite(sprite)
        {
        }

        FloatRect GetGlobalBounds(Vec2f position) const
        {
            const auto& localBounds = sprite.GetBounds();
            const auto pivot = sprite.GetPivot();

            position.x -= pivot.x;
            position.y -= pivot.y;

            return FloatRect(
                position.x + localBounds.x, position.y + localBounds.y,
                localBounds.width, localBounds.height
            );
        }
    };
} // Maize
