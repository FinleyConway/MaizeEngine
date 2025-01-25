#pragma once

#include <Maize.h>

#include "Components/Grid.h"
#include "Components/PlaceChunkTile.h"
#include "Utils/RailTile.h"

struct PlaceRailData;
struct RailSelector;
struct RailTile;

class MineRailPlacement
{
public:
    static void SelectTile(Maize::SystemState s, const Maize::Position& p, const RailSelector& selector);

    static void PlaceTile(Maize::SystemState s, Maize::Entity e, Maize::MeshRenderer& meshRenderer,
                          Grid<RailTile>& grid, const PlaceChunkTile<PlaceRailData>& placeTile);

private:
    // TODO: remove out of system sooner or later
    static std::array<sf::Vertex, 6> CreateQuad(Maize::Vec2i topLeft, Maize::Vec2i size, const Maize::IntRect& atlas, Maize::Vec2i pivot);

    static size_t CalculateMeshIndex(Maize::Vec2i localPosition, Maize::Vec2i chunkSize);
};
