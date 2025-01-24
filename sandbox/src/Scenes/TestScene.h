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
        m_Texture = std::make_shared<sf::Texture>();
        bool created = m_Texture->loadFromFile("/home/finley/CppProjects/MaizeEngine/sandbox/assets/TestRailAutoTile.png");

        CreateSingleton<ChunkManager>(
            Maize::Vec2i(32, 32),
            Maize::Vec2i(32, 32)
        );

        CreateEntity(
            Maize::Position(0, 0),
            Maize::Camera(2)
        );

        CreateEntity(
            Maize::Position(0, 0),
            Maize::SpriteRenderer(Maize::Sprite(m_Texture, {0, 0, 32, 32}, { 0, 32 })),
            RailSelector(m_Texture, GetAutoTiles())
        );

        CreateEntity(
            Maize::Position(0, 0),
            Maize::SpriteRenderer(Maize::Sprite(m_Texture, {0, 0, 32, 32}, { 0, 32 })),
            RailController(),
            RailRotations(GetCartDirs())
        );

        AddSystem<Maize::Position, Maize::SpriteRenderer, RailSelector>(
            "Choose Rail Type", flecs::OnUpdate, RailTileChooser::ChooseRailType
        );

        AddSystem<const Maize::Position, const RailSelector>(
            "Rail Select Tile", flecs::OnUpdate, MineRailPlacement::SelectTile
        );

        AddSystem<Maize::MeshRenderer, Grid<RailTile>, const PlaceChunkTile<PlaceRailData>>(
            "Rail Place Tile", flecs::OnUpdate, MineRailPlacement::PlaceTile
        );

        AddSystem<Maize::Position, RailController, const RailRotations>(
            "Rail Controller", flecs::OnUpdate, MineCarMovement::Move
        );
    }

    virtual void OnEnd() override {}

private:
    static std::vector<Maize::IntRect> GetCartDirs()
    {
        std::vector<Maize::IntRect> directions;

        for (uint8_t i = 0; i < 8; i++)
        {
            directions.emplace_back(i * 32, 0, 32, 32);
        }

        return directions;
    }

    static std::unordered_map<std::underlying_type_t<Rail::Type>, Maize::IntRect> GetAutoTiles()
    {
        std::unordered_map<std::underlying_type_t<Rail::Type>, Maize::IntRect> autoTiles;

        autoTiles.emplace(20, Maize::IntRect(0, 32, 32, 32));
        autoTiles.emplace(80, Maize::IntRect(32, 32, 32, 32));
        autoTiles.emplace(84, Maize::IntRect(64, 32, 32, 32));
        autoTiles.emplace(21, Maize::IntRect(96, 32, 32, 32));
        autoTiles.emplace(81, Maize::IntRect(128, 32, 32, 32));
        autoTiles.emplace(85, Maize::IntRect(160, 32, 32, 32));

        autoTiles.emplace(5, Maize::IntRect(0, 64, 32, 32));
        autoTiles.emplace(65, Maize::IntRect(32, 64, 32, 32));
        autoTiles.emplace(69, Maize::IntRect(64, 64, 32, 32));
        autoTiles.emplace(17, Maize::IntRect(96, 64, 32, 32));
        autoTiles.emplace(68, Maize::IntRect(128, 64, 32, 32));

        return autoTiles;
    }

private:
    std::shared_ptr<sf::Texture> m_Texture;
};
