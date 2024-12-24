#pragma once

#include <SFML/Graphics.hpp>

#include "Maize/Math/Rect.h"

namespace Maize
{
    class Mesh
    {
    public:
        /**
         * Assigns a new mesh and automatically generate bounds
         * @param mesh A contiguous data structure that contains a mesh
         */
        void AddVertices(std::span<sf::Vertex> mesh);

        /**
         * Assigns a new mesh and pre-defined bounds
         * @param mesh A contiguous data structure that contains a mesh
         * @param bounds The bounds of the mesh
         */
        void AddVertices(std::span<sf::Vertex> mesh, const FloatRect& bounds);

        /**
         * Get the mesh's vertex array.
         * @return The mesh consisting position, uv and colour.
         */
        const std::vector<sf::Vertex>& GetVertices() const;

        /**
         * Get the mesh's vertex array count.
         */
        size_t GetVertexCount() const;

        /**
         * The local bounds of the mesh.
         */
        const FloatRect& GetBounds() const;

        /**
         * Remove mesh.
         */
        void Clear();

    private:
        FloatRect GetMeshBounds();

    private:
        std::vector<sf::Vertex> m_Mesh;
        FloatRect m_Bounds;
    };
} // Maize
