#pragma once

#include <Maize.h>

#include "ChunkManager.h"
#include "Grid.h"
#include "MineCarMovement.h"
#include "MineRailPlacement.h"
#include "RailController.h"
#include "RailSelector.h"
#include "Rail.h"
#include "RailRotations.h"

class TestScene final : public Maize::Scene
{
public:
    virtual void OnStart() override
    {
        m_TextureRails = std::make_shared<sf::Texture>();
        if (!m_TextureRails->loadFromFile("/home/finley/CLionProjects/MaizeEngine/sandbox/assets/TestRailDir.png"))
            return;

        std::vector<Maize::IntRect> mineCarRects;
        mineCarRects.reserve(128);

        for (uint8_t y = 0; y < 8; y++)
            for (uint8_t x = 0; x < 4; x++)
            {
                mineCarRects.emplace_back(x * 128, y * 128, 128, 128);
            }

        CreateSingleton<ChunkManager>(
            Maize::Vec2i(32, 32),
            Maize::Vec2i(64, 64)
        );

        CreateEntity(Maize::Vec2f(0, 0), Maize::Camera(1));
        CreateEntity(
            Maize::Vec2f(0, 0),
            Maize::SpriteRenderer(Maize::Sprite(m_TextureRails, {0, 0, 64, 64}, { 0, 64 })),
            RailSelector(m_TextureRails, GetRailAtlas())
        );

        AddSystem<Maize::Position, Maize::SpriteRenderer, RailSelector>("Choose Rail Type", flecs::OnUpdate, MineRailPlacement::ChooseRailType);
        AddSystem<const Maize::Position, const RailSelector>("Rail Select Tile", flecs::OnUpdate, MineRailPlacement::SelectTile);
        AddSystem<Maize::MeshRenderer, Grid<RailTile>, const PlaceGridTile>(
            "Rail Place Tile", flecs::OnUpdate, MineRailPlacement::PlaceTile
        );
        AddSystem<Maize::Position, RailController, const RailRotations>("Rail Controller", flecs::OnUpdate, MineCarMovement::Move);
    }

    virtual void OnEnd() override {}

private:
    static std::unordered_map<Rail::Type, Maize::IntRect> GetRailAtlas()
    {
        std::unordered_map<Rail::Type, Maize::IntRect> rails;

        rails.emplace(Rail::Type::Vertical, Maize::IntRect(0, 0, 64, 64));
        rails.emplace(Rail::Type::NESW, Maize::IntRect(64, 0, 64, 64));
        rails.emplace(Rail::Type::Horizontal, Maize::IntRect(128, 0, 64, 64));
        rails.emplace(Rail::Type::NWSE, Maize::IntRect(448, 0, 64, 64));

        return rails;
    }

private:
    std::shared_ptr<sf::Texture> m_TextureRails;
    std::shared_ptr<sf::Texture> m_TextureMineCar;
};
