#pragma once

#include "Maize/Math/Vec2.h"
#include "Maize/Rendering/Mesh.h"

// https://www.youtube.com/watch?v=11c9rWRotJ8
// https://www.sfml-dev.org/tutorials/2.6/graphics-vertex-array.php

namespace Maize {

    struct MeshRenderer
    {
        Mesh mesh;
        std::weak_ptr<sf::Texture> texture;

        MeshRenderer() = default;
        MeshRenderer(const Mesh& mesh) : mesh(mesh) { }
        MeshRenderer(const std::weak_ptr<sf::Texture>& texture) : texture(texture) { }
        MeshRenderer(const Mesh& mesh, const std::shared_ptr<sf::Texture>& texture)
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