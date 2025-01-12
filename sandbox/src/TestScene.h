#pragma once

#include <Maize.h>

#include "ChunkManager.h"
#include "Grid.h"
#include "MineCarMovement.h"
#include "MineRailPlacement.h"
#include "RailController.h"
#include "RailSelector.h"
#include "Rail.h"

class TestScene final : public Maize::Scene
{
public:
    virtual void OnStart() override
    {
        m_TextureRails = std::make_shared<sf::Texture>();
        if (!m_TextureRails->loadFromFile("/home/finley/CLionProjects/MaizeEngine/sandbox/assets/tileset-16x16.png"))
            return;

        m_TextureMineCar = std::make_shared<sf::Texture>();
        if (!m_TextureMineCar->loadFromFile("/home/finley/CLionProjects/MaizeEngine/sandbox/assets/lpc-mine-cart-carts-angles.png"))
            return;

        auto mineCar = Maize::Sprite(m_TextureMineCar, {0, 0, 64, 64 }, {0, -32});

        CreateSingleton<ChunkManager>(
            Maize::Vec2i(32, 32),
            Maize::Vec2i(16, 16)
        );

        CreateEntity(Maize::Vec2f(0, 0), Maize::Camera(2));
        CreateEntity(Maize::Vec2f(0, 0), RailSelector(m_TextureRails, GetRailAtlas()));
        CreateEntity(Maize::Vec2f(0, 0), Maize::SpriteRenderer(mineCar), RailController({0,0}, GetMineCarAtlas()));

        AddSystem<RailSelector>("Choose Rail Type", flecs::OnUpdate, MineRailPlacement::ChooseRailType);
        AddSystem<const RailSelector>("Rail Select Tile", flecs::OnUpdate, MineRailPlacement::SelectTile);
        AddSystem<Maize::MeshRenderer, Grid<RailTile>, const PlaceGridTile>(
            "Rail Place Tile", flecs::OnUpdate, MineRailPlacement::PlaceTile
        );
        AddSystem<Maize::Position, RailController>("Rail Controller", flecs::OnUpdate, MineCarMovement::Move);
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

    static std::unordered_map<Rail::Type, std::array<Maize::IntRect, 3>>  GetMineCarAtlas()
    {
        std::unordered_map<Rail::Type, std::array<Maize::IntRect, 3>> mineCart;

        constexpr auto straight = Maize::IntRect(0, 0, 64, 64);
        constexpr auto horizontal = Maize::IntRect(64, 0, 64, 64);
        constexpr auto diaRight = Maize::IntRect(128, 0, 64, 64);
        constexpr auto diaLeft = Maize::IntRect(192, 0, 64, 64);

        mineCart.emplace(Rail::Type::NorthRight, std::array<Maize::IntRect, 3>({ horizontal, diaRight, straight }));
        mineCart.emplace(Rail::Type::NorthLeft,  std::array<Maize::IntRect, 3>({ horizontal, diaRight, straight }));
        mineCart.emplace(Rail::Type::SouthRight,  std::array<Maize::IntRect, 3>({ straight, diaRight, horizontal }));
        mineCart.emplace(Rail::Type::SouthLeft,  std::array<Maize::IntRect, 3>({ horizontal, diaLeft, straight }));

        return mineCart;
    }

private:
    std::shared_ptr<sf::Texture> m_TextureRails;
    std::shared_ptr<sf::Texture> m_TextureMineCar;
};
