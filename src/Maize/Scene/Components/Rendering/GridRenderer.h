#pragma once

#include "Maize/Rendering/MeshGrid.h"
#include "Maize/Math/Rect.h"
#include "Maize/Math/Vec2.h"

namespace Maize
{
    struct GridRenderer
    {
        MeshGrid mesh;
        std::weak_ptr<sf::Texture> texture;

        GridRenderer() = default;
        GridRenderer(const MeshGrid& mesh) : mesh(mesh) { }
        GridRenderer(const std::weak_ptr<sf::Texture>& texture) : texture(texture) { }
        GridRenderer(const MeshGrid& mesh, const std::weak_ptr<sf::Texture>& texture)
            : mesh(mesh), texture(texture) { }

        FloatRect GetGlobalBounds(Vec2f position) const
        {
            const auto& localBounds = mesh.GetBounds();

            return FloatRect(
                position.x + localBounds.x, position.y + localBounds.y,
                localBounds.width, localBounds.height
            );
        }
    };
} // Maize
