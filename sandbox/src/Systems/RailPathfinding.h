#pragma once

#include <Maize.h>
#include <queue>

#include "Components/ChunkManager.h"
#include "Components/Grid.h"
#include "Components/RailController.h"
#include "Components/RailPathRequest.h"
#include "Utils/GridConversion.h"
#include "Utils/Rail.h"
#include "Utils/RailTile.h"

class RailPathfinding
{
public:
    static void RequestPath(Maize::SystemState s, Maize::Entity e, const RailController& controller, RailPathRequest& request)
    {
        const auto* chunkManager = s.GetSingleton<ChunkManager>();

        GAME_ASSERT(chunkManager != nullptr, "ChunkManager is nullptr");

        e.RemoveComponent<RailPathRequest>();
    }

private:
};
