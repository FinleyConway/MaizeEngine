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

    static void PlaceTile(Maize::SystemState s, Maize::Entity e, Maize::GridRenderer& gridRenderer,
                          Grid<RailTile>& grid, const PlaceChunkTile<PlaceRailData>& placeTile);

private:
};
