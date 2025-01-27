#include "PrecompiledHeader.h"
#include "Maize/Rendering/MeshGrid.h"

namespace Maize
{
    MeshGrid::MeshGrid(Vec2i size, Vec2i cellSize) :
        Mesh(
            size.x * size.y * 6,
            { 0, 0, static_cast<float>(size.x * cellSize.x), static_cast<float>(size.y * cellSize.y) }
        )
    {

    }

    void MeshGrid::Set(Vec2i pos, Vec2i cellSize, Vec2i size, const IntRect& atlas, Vec2i gridOffset)
    {
        PROFILE_FUNCTION();

        CORE_ASSERT(pos.x >= 0 && pos.y >= 0, "Position must be greater-equal than 0");
        CORE_ASSERT(size.x > 0 && size.y > 0, "Size must be greater than 0");
        CORE_ASSERT(!m_Mesh.empty(), "Mesh grid is empty");

        const auto position = Vec2i(pos.x, -pos.y) * cellSize;
        const auto quad = CreateQuad(position, cellSize, atlas, gridOffset);
        const size_t index = CalculateMeshIndex(pos, size);

        std::ranges::copy(quad, m_Mesh.begin() + index);
    }

    void MeshGrid::Remove(Vec2i pos, Vec2i size)
    {
        PROFILE_FUNCTION();

        CORE_ASSERT(pos.x >= 0 && pos.y >= 0, "Position must be greater-equal than 0");
        CORE_ASSERT(size.x > 0 && size.y > 0, "Size must be greater than 0");
        CORE_ASSERT(!m_Mesh.empty(), "Mesh grid is empty");

        const size_t index = CalculateMeshIndex(pos, size);

        std::ranges::copy(std::array<sf::Vertex, 6>(), m_Mesh.begin() + index);
    }

    void MeshGrid::Resize(Vec2i size, Vec2i cellSize)
    {
        PROFILE_FUNCTION();

        CORE_ASSERT(size.x > 0 && size.y > 0, "Size must be greater than 0");

        m_Mesh.resize(size.x * size.y * 6);
        m_Bounds = { 0, 0, static_cast<float>(size.x * cellSize.x), static_cast<float>(size.y * cellSize.y) };
    }

    std::array<sf::Vertex, 6> MeshGrid::CreateQuad(Vec2i topLeft, Vec2i size, const IntRect& atlas, Vec2i pivot)
    {
        PROFILE_FUNCTION();

        std::array<sf::Vertex, 6> quad;

        const auto bottomRight = topLeft + size;

        // position
        // first triangle
        quad[0].position = sf::Vector2f(topLeft.x, topLeft.y);
        quad[1].position = sf::Vector2f(topLeft.x, bottomRight.y);
        quad[2].position = sf::Vector2f(bottomRight.x, topLeft.y);

        // second triangle
        quad[3].position = sf::Vector2f(bottomRight.x, topLeft.y);
        quad[4].position = sf::Vector2f(topLeft.x, bottomRight.y);
        quad[5].position = sf::Vector2f(bottomRight.x, bottomRight.y);

        // apply pivot transformation
        for (auto& v : quad)
        {
            v.position -= sf::Vector2f(pivot.x, pivot.y);
        }

        // atlas position
        // first triangle
        quad[0].texCoords = sf::Vector2f(atlas.x, atlas.y);
        quad[1].texCoords = sf::Vector2f(atlas.x, atlas.y + atlas.height);
        quad[2].texCoords = sf::Vector2f(atlas.x + atlas.width, atlas.y);

        // second triangle
        quad[3].texCoords = sf::Vector2f(atlas.x + atlas.width, atlas.y);
        quad[4].texCoords = sf::Vector2f(atlas.x, atlas.y + atlas.height);
        quad[5].texCoords = sf::Vector2f(atlas.x + atlas.width, atlas.y + atlas.height);

        return quad;
    }

    size_t MeshGrid::CalculateMeshIndex(Vec2i localPosition, Vec2i chunkSize)
    {
        PROFILE_FUNCTION();

        constexpr uint8_t verticesPerQuad = 6;
        const size_t quadIndex = localPosition.x + localPosition.y * chunkSize.x;

        return quadIndex * verticesPerQuad;
    }
} // Maize