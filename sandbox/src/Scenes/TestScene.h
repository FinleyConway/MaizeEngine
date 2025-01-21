#pragma once

#include <Maize.h>

#include "Components/Grid.h"
#include "Components/ChunkManager.h"
#include "Components/RailController.h"
#include "Components/RailSelector.h"
#include "Components/RailRotations.h"
#include "Components/PlaceChunkTile.h"
#include "Systems/MineCarMovement.h"
#include "Systems/MineRailPlacement.h"
#include "Systems/RailTileChooser.h"
#include "Utils/PlaceRailData.h"
#include "Utils/FuzzyShape.h"
#include "Utils/RailTile.h"
#include "Utils/Rail.h"

class TestScene final : public Maize::Scene
{
public:
    virtual void OnStart() override
    {
        m_TextureRails = std::make_shared<sf::Texture>();
        if (!m_TextureRails->loadFromFile("/home/finley/CLionProjects/MaizeEngine/sandbox/assets/TestRailAutoTile.png"))
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
            Maize::Vec2i(32, 32)
        );

        CreateEntity(Maize::Vec2f(0, 0), Maize::Camera(2));
        CreateEntity(
            Maize::Vec2f(0, 0),
            Maize::SpriteRenderer(Maize::Sprite(m_TextureRails, {0, 0, 32, 32}, { 0, 32 })),
            RailSelector(m_TextureRails, GetRailAtlas(), GetAutoTiles())
        );

        AddSystem<Maize::Position, Maize::SpriteRenderer, RailSelector>("Choose Rail Type", flecs::OnUpdate, RailTileChooser::ChooseRailType);
        AddSystem<const Maize::Position, const RailSelector>("Rail Select Tile", flecs::OnUpdate, MineRailPlacement::SelectTile);
        AddSystem<Maize::MeshRenderer, Grid<RailTile>, const PlaceChunkTile<PlaceRailData>>(
            "Rail Place Tile", flecs::OnUpdate, MineRailPlacement::PlaceTile
        );

        AddSystem<Maize::Position, RailController, const RailRotations>("Rail Controller", flecs::OnUpdate, MineCarMovement::Move);
    }

    virtual void OnEnd() override {}

private:
    static std::unordered_map<Rail::Type, Maize::IntRect> GetRailAtlas()
    {
        std::unordered_map<Rail::Type, Maize::IntRect> rails;

        rails.emplace(Rail::Type::Vertical, Maize::IntRect(0, 0, 32, 32));
        rails.emplace(Rail::Type::Horizontal, Maize::IntRect(32, 0, 32, 32));

        rails.emplace(Rail::Type::Diagonal, Maize::IntRect(64, 0, 32, 32));
        rails.emplace(Rail::Type::ADiagonal, Maize::IntRect(96, 0, 32, 32));

        rails.emplace(Rail::Type::NorthLeft, Maize::IntRect(0, 32, 32, 32));
        rails.emplace(Rail::Type::NorthRight, Maize::IntRect(32, 32, 32, 32));

        rails.emplace(Rail::Type::SouthLeft, Maize::IntRect(64, 32, 32, 32));
        rails.emplace(Rail::Type::SouthRight, Maize::IntRect(96, 32, 32, 32));

        return rails;
    }

    static std::unordered_map<uint8_t, Maize::IntRect> GetAutoTiles()
    {
        std::unordered_map<uint8_t, Maize::IntRect> autoTiles;

        autoTiles.emplace(17, Maize::IntRect(0, 0, 32, 32));
        autoTiles.emplace(68, Maize::IntRect(32, 0, 32, 32));
        autoTiles.emplace(34, Maize::IntRect(64, 0, 32, 32));
        autoTiles.emplace(136, Maize::IntRect(96, 0, 32, 32));
        autoTiles.emplace(65, Maize::IntRect(0, 32, 32, 32));
        autoTiles.emplace(5, Maize::IntRect(32, 32, 32, 32));
        autoTiles.emplace(80, Maize::IntRect(64, 32, 32, 32));
        autoTiles.emplace(20, Maize::IntRect(96, 32, 32, 32));
        autoTiles.emplace(144, Maize::IntRect(0, 64, 32, 32));
        autoTiles.emplace(18, Maize::IntRect(32, 64, 32, 32));
        autoTiles.emplace(33, Maize::IntRect(64, 64, 32, 32));
        autoTiles.emplace(9, Maize::IntRect(96, 64, 32, 32));
        autoTiles.emplace(132, Maize::IntRect(0, 96, 32, 32));
        autoTiles.emplace(36, Maize::IntRect(32, 96, 32, 32));
        autoTiles.emplace(66, Maize::IntRect(64, 96, 32, 32));
        autoTiles.emplace(72, Maize::IntRect(96, 96, 32, 32));

        return autoTiles;
    }

private:
    std::shared_ptr<sf::Texture> m_TextureRails;
    std::shared_ptr<sf::Texture> m_TextureMineCar;
};
