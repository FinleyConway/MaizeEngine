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
        if (!m_TextureRails->loadFromFile("/home/finley/CppProjects/MaizeEngine/sandbox/assets/tileset-16x16.png"))
            return;

        m_TextureMineCar = std::make_shared<sf::Texture>();
        if (!m_TextureMineCar->loadFromFile("/home/finley/CppProjects/MaizeEngine/sandbox/assets/MineCar.png"))
            return;

        auto mineCar = Maize::Sprite(m_TextureMineCar, {0, 0, 128, 128 }, { 64, -64 });

        std::vector<Maize::IntRect> mineCarRects;
        mineCarRects.reserve(128);

        for (uint8_t y = 0; y < 128; y++)
            for (uint8_t x = 0; x < 16; x++)
            {
                mineCarRects.emplace_back(x * 128, y * 128, 128, 128);
            }

        CreateSingleton<ChunkManager>(
            Maize::Vec2i(32, 32),
            Maize::Vec2i(16, 16)
        );

        CreateEntity(Maize::Vec2f(0, 0), Maize::Camera(2));
        CreateEntity(Maize::Vec2f(0, 0), RailSelector(m_TextureRails, GetRailAtlas()));
        CreateEntity(Maize::Vec2f(0, 0), Maize::SpriteRenderer(mineCar), RailController({ 0, 0 }), RailRotations(mineCarRects));

        AddSystem<RailSelector>("Choose Rail Type", flecs::OnUpdate, MineRailPlacement::ChooseRailType);
        AddSystem<const RailSelector>("Rail Select Tile", flecs::OnUpdate, MineRailPlacement::SelectTile);
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

        rails.emplace(Rail::Type::Vertical,   Maize::IntRect(16 , 0, 16, 16));
        rails.emplace(Rail::Type::Horizontal, Maize::IntRect(48 , 32, 16, 16));
        rails.emplace(Rail::Type::NorthRight, Maize::IntRect(128, 0, 16, 16));
        rails.emplace(Rail::Type::NorthLeft,  Maize::IntRect(144, 0, 16, 16));
        rails.emplace(Rail::Type::SouthRight, Maize::IntRect(128, 16, 16, 16));
        rails.emplace(Rail::Type::SouthLeft,  Maize::IntRect(144, 16, 16, 16));

        return rails;
    }

private:
    std::shared_ptr<sf::Texture> m_TextureRails;
    std::shared_ptr<sf::Texture> m_TextureMineCar;
};
