#pragma once

#include <Maize.h>

#include "GridConversion.h"
#include "ChunkManager.h"
#include "RailSelector.h"
#include "PlaceGridTile.h"
#include "RailTile.h"
#include "Grid.h"

class MineRailPlacement
{
public:
    static void SelectTile(Maize::SystemState s, Maize::Entity e, const Maize::Position& p, const RailSelector& selector)
    {
        auto* input = s.GetSingleton<Maize::Input>();
        auto* chunkManager = s.GetSingleton<ChunkManager>();

        GAME_ASSERT(chunkManager != nullptr, "ChunkManager is nullptr");

        const auto gridPosition = GridConversion::PixelToGrid(p, chunkManager->cellSize);
        const auto chunkPosition = GridConversion::GridToChunk(gridPosition, chunkManager->chunkSize);
        const auto localPosition = GridConversion::GridToChunkLocal(gridPosition, chunkManager->chunkSize);
        auto entity = chunkManager->TryGetChunk(chunkPosition);

        ImGui::Begin("Rail");
        ImGui::Text("Mouse Position: %s", p.ToString().c_str());
        ImGui::Text("Grid Position: %s", gridPosition.ToString().c_str());
        ImGui::Text("Chunk Position: %s", chunkPosition.ToString().c_str());
        ImGui::Text("Local Position: %s", localPosition.ToString().c_str());
        ImGui::End();

        static bool isLocked = false;

        if (input->GetMouseButtonHeld(Maize::MouseCode::Left))
        {
            if (entity.IsNull())
            {
                const auto chunkGridPosition = GridConversion::ChunkToGrid(chunkPosition, chunkManager->chunkSize);
                const auto pixelPosition = GridConversion::GridToPixel(chunkGridPosition, chunkManager->cellSize);

                entity = s.CreateEntity(pixelPosition,
                    Maize::MeshRenderer(selector.texture),
                    Grid<RailTile>(chunkManager->chunkSize)
                );

                chunkManager->chunks[chunkPosition] = entity;
            }

            entity.AddComponent(
                PlaceGridTile(
                    chunkPosition,
                    localPosition,
                    selector.GetAtlas(selector.currentType),
                    selector.gridOffset,
                    selector.currentType
                )
            );
        }
        if (input->GetMouseButtonHeld(Maize::MouseCode::Right))
        {
            if (!entity.IsNull())
            {
                entity.AddComponent(
                    PlaceGridTile(
                        chunkPosition,
                        localPosition,
                        selector.GetAtlas(Rail::Type::None),
                        selector.gridOffset,
                        Rail::Type::None
                    )
                );
            }
        }
    }

    static void PlaceTile(Maize::SystemState s, Maize::Entity e, Maize::MeshRenderer& meshRenderer,
        Grid<RailTile>& grid, const PlaceGridTile& placeTile)
    {
        const auto* chunkManager = s.GetSingleton<ChunkManager>();

        GAME_ASSERT(chunkManager != nullptr, "ChunkManager is nullptr");

        const auto chunkSize = chunkManager->chunkSize;
        const auto cellSize = chunkManager->cellSize;
        const auto position = Maize::Vec2i(placeTile.local.x, -placeTile.local.y) * cellSize;
        const auto quad = CreateQuad(position, cellSize, placeTile.atlas, placeTile.gridOffset);
        const size_t index = CalculateMeshIndex(placeTile.local, chunkSize);

        grid.Set(placeTile.local, chunkSize, { placeTile.railType });

        /// look into a better way of doing this?
        auto meshArrayCopy = meshRenderer.mesh.GetVertices();
        if (meshArrayCopy.empty())
        {
            meshArrayCopy.resize(chunkSize.x * chunkSize.y * 6);
        }
        std::ranges::copy(quad, meshArrayCopy.begin() + index);
        meshRenderer.mesh.AddVertices(meshArrayCopy, chunkManager->GetChunkBounds());
        /// ---------------

        e.RemoveComponent<PlaceGridTile>();
    }

private:
    static std::array<sf::Vertex, 6> CreateQuad(Maize::Vec2i topLeft, Maize::Vec2i size, const Maize::IntRect& atlas, Maize::Vec2i pivot)
    {
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

    static size_t CalculateMeshIndex(Maize::Vec2i localPosition, Maize::Vec2i chunkSize)
    {
        constexpr uint32_t verticesPerQuad = 6;
        const size_t quadIndex = localPosition.x + localPosition.y * chunkSize.x;

        return quadIndex * verticesPerQuad;
    }
};
