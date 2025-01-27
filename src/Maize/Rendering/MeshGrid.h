#pragma once

#include "Maize/Math/Vec2.h"
#include "Maize/Rendering/Mesh.h"

namespace Maize
{
    class MeshGrid final : public Mesh
    {
    public:
        MeshGrid() = default;

        MeshGrid(Vec2i size, Vec2i cellSize);

        virtual ~MeshGrid() override = default;

        /**
         * Set a quad to a position in a mesh.
         * @param pos The grid position to placed at.
         * @param cellSize The size of the quad.
         * @param size The size of the grid.
         * @param atlas The texture atlas of the grid.
         * @param gridOffset The offset of the quad in the grid.
         */
        void Set(Vec2i pos, Vec2i cellSize, Vec2i size, const IntRect& atlas, Vec2i gridOffset);

        /**
         * Remove the quad from the grid by setting the quad back to default (empty).
         * @param pos The grid position to be removed at.
         * @param size The size of the grid.
         */
        void Remove(Vec2i pos, Vec2i size);

        /**
         * Resize mesh grid.
         * @param size The new size.
         * @param cellSize The size of the quads.
         */
        void Resize(Vec2i size, Vec2i cellSize);

    private:
        static std::array<sf::Vertex, 6> CreateQuad(Vec2i topLeft, Vec2i size, const IntRect& atlas, Vec2i pivot);

        static size_t CalculateMeshIndex(Vec2i localPosition, Vec2i chunkSize);
    };
} // Maize
