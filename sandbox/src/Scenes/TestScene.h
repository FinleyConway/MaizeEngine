#pragma once

#include <Maize.h>

#include "Components/Grid.h"
#include "Components/ChunkManager.h"
#include "Components/RailController.h"
#include "Components/RailSelector.h"
#include "Components/RailRotations.h"
#include "Components/PlaceChunkTile.h"
#include "Systems/MineCarMovement.h"
#include "Systems/MineCarRotate.h"
#include "Systems/MineRailPlacement.h"
#include "Systems/RailTileChooser.h"
#include "Utils/RailTurnDirection.h"
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
        bool created = m_Texture->loadFromFile("TestRailAutoTile.png");

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
            RailSelector(m_Texture, GetAutoTiles(), GetQuadrantShapes())
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

        AddSystem<Maize::GridRenderer, Grid<RailTile>, const PlaceChunkTile<PlaceRailData>>(
            "Rail Place Tile", flecs::OnUpdate, MineRailPlacement::PlaceTile
        );

        AddSystem<Maize::Position, RailController>(
            "Rail Movement", flecs::OnUpdate, MineCarMovement::Move
        );

        AddSystem<Maize::SpriteRenderer, RailController, const RailRotations>(
            "Rail Rotate", flecs::OnUpdate, MineCarRotate::Rotate
        );
    }

    virtual void OnEnd() override {}

private:
    static std::vector<RailTurnDirection> GetCartDirs()
    {
        std::vector<RailTurnDirection> directions;

        // handles N->E, E->N rotations
        directions.emplace_back(
            Rail::ToBitset(Rail::Dir::N),
            Rail::ToBitset(Rail::Dir::E),
            std::vector<Maize::IntRect>
            {
                { 0, 0, 32, 32 },
                { 32, 0, 32, 32 },
                { 64, 0, 32, 32 },
            }
        );

        // handles E->S, S->E rotations
        directions.emplace_back(
            Rail::ToBitset(Rail::Dir::E),
            Rail::ToBitset(Rail::Dir::S),
            std::vector<Maize::IntRect>
            {
                { 64, 0, 32, 32 },
                { 96, 0, 32, 32 },
                { 128, 0, 32, 32 },
            }
        );

        // handles S->W, W->S rotations
        directions.emplace_back(
            Rail::ToBitset(Rail::Dir::S),
            Rail::ToBitset(Rail::Dir::W),
            std::vector<Maize::IntRect>
            {
                { 128, 0, 32, 32 },
                { 160, 0, 32, 32 },
                { 192, 0, 32, 32 },
            }
        );

        // handles W->N, N->W rotations
        directions.emplace_back(
            Rail::ToBitset(Rail::Dir::W),
            Rail::ToBitset(Rail::Dir::N),
            std::vector<Maize::IntRect>
            {
                { 192, 0, 32, 32 },
                { 224, 0, 32, 32 },
                { 0, 0, 32, 32 },
            }
        );

        return directions;
    }

    static std::unordered_map<Rail::TypeBits, Maize::IntRect> GetAutoTiles()
    {
        std::unordered_map<Rail::TypeBits, Maize::IntRect> autoTiles;

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

    static std::vector<FuzzyShape> GetQuadrantShapes()
    {
        // order matters, lower the index, higher the priority.
        const std::vector shapes =
        {
            // junctions
            FuzzyShape(0b01000100, 0b01000100, std::array {
                Rail::Type::Horizontal,  Rail::Type::TJunctionDown, Rail::Type::Horizontal,
                Rail::Type::Horizontal,  Rail::Type::CrossJunction, Rail::Type::Horizontal,
                Rail::Type::Horizontal,  Rail::Type::TJunctionUp,   Rail::Type::Horizontal
            }), // horizontal down/up/both

            FuzzyShape(0b00010001, 0b00010001, std::array {
                Rail::Type::Vertical,       Rail::Type::Vertical,       Rail::Type::Vertical,
                Rail::Type::TJunctionLeft,  Rail::Type::CrossJunction,  Rail::Type::TJunctionRight,
                Rail::Type::Vertical,       Rail::Type::Vertical,       Rail::Type::Vertical
            }), // vertical left/right/both


            // normal rails
            FuzzyShape(0b00000000, 0b11111111, std::array {
                Rail::Type::Horizontal, Rail::Type::Vertical, Rail::Type::Horizontal,
                Rail::Type::Horizontal, Rail::Type::Vertical, Rail::Type::Horizontal,
                Rail::Type::Horizontal, Rail::Type::Vertical, Rail::Type::Horizontal
            }), // default

            FuzzyShape(0b11010111, 0b00010000, std::array {
                Rail::Type::SouthLeft, Rail::Type::Vertical, Rail::Type::SouthRight,
                Rail::Type::SouthLeft, Rail::Type::Vertical, Rail::Type::SouthRight,
                Rail::Type::SouthLeft, Rail::Type::Vertical, Rail::Type::SouthRight
            }), // north

            FuzzyShape(0b01011111, 0b01000000, std::array {
                Rail::Type::SouthLeft,  Rail::Type::SouthLeft,  Rail::Type::SouthLeft,
                Rail::Type::Horizontal, Rail::Type::Horizontal, Rail::Type::Horizontal,
                Rail::Type::NorthLeft,  Rail::Type::NorthLeft,  Rail::Type::NorthLeft
            }), // east

            FuzzyShape(0b01111101, 0b00000001, std::array {
                Rail::Type::NorthLeft, Rail::Type::Vertical, Rail::Type::NorthRight,
                Rail::Type::NorthLeft, Rail::Type::Vertical, Rail::Type::NorthRight,
                Rail::Type::NorthLeft, Rail::Type::Vertical, Rail::Type::NorthRight
            }), // south

            FuzzyShape(0b11110101, 0b00000100, std::array {
                Rail::Type::SouthRight,  Rail::Type::SouthRight, Rail::Type::SouthRight,
                Rail::Type::Horizontal,  Rail::Type::Horizontal, Rail::Type::Horizontal,
                Rail::Type::NorthRight,  Rail::Type::NorthRight, Rail::Type::NorthRight
            }), // west
        };

        return shapes;
    }

private:
    std::shared_ptr<sf::Texture> m_Texture;
};
