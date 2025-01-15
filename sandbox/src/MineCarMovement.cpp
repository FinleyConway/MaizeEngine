#include "MineCarMovement.h"

#include "ChunkManager.h"
#include "Grid.h"
#include "GridConversion.h"
#include "RailController.h"
#include "Rail.h"
#include "RailTile.h"
#include "RailRotations.h"

void MineCarMovement::Move(Maize::SystemState s, Maize::Entity e, Maize::Position& position, RailController& controller, const RailRotations& rotations)
{
    auto* input = s.GetSingleton<Maize::Input>();
    const auto* chunkManager = s.GetSingleton<ChunkManager>();

    GAME_ASSERT(chunkManager != nullptr, "ChunkManager is nullptr");

    ImGui::Begin("Mine Car Stats");
    ImGui::Text("Speed: %f", controller.speed);
    ImGui::Text("Current Dir: %s", Rail::DirToStr(controller.travellingDirection).data());
    ImGui::Text("Current Dir: %s", controller.isTurning ? "Turning" : "Not Turning");
    ImGui::Text("Current Time To Next: %f", controller.currentTime);
    ImGui::Text("Last Position: %s", controller.lastPos.ToString().data());
    ImGui::Text("Next Position: %s", controller.nextPos.ToString().data());
    ImGui::Text("Next Direction: %s", Rail::TypeToStr(controller.nextRail).data());
    ImGui::Text("Turning Time: %f", controller.turningTime);
    ImGui::End();

    if (input->GetButtonHeld(Maize::KeyCode::W))
    {
        if (position.ApproxOf(controller.nextPos))
        {
            HandleDirection(chunkManager, controller);
        }

        HandleTurning(e, controller, rotations);

        if (controller.nextRail != Rail::Type::None)
        {
            controller.currentTime += controller.speed * s.DeltaTime();
            controller.currentTime = std::clamp(controller.currentTime, 0.0f, 1.0f);

            position = controller.lastPos.LerpTo(controller.nextPos, controller.currentTime);
        }
    }
}

void MineCarMovement::HandleDirection(const ChunkManager* chunkManager, RailController& controller)
{
    // get the current tile check if it's within the grid.
    const auto gridPosition = GridConversion::PixelToGrid(controller.nextPos, chunkManager->cellSize);
    const auto chunkPosition = GridConversion::GridToChunk(gridPosition, chunkManager->chunkSize);
    const auto entity = chunkManager->TryGetChunk(chunkPosition);

    if (const auto* grid = entity.TryGetComponent<Grid<RailTile>>())
    {
        // get the tile and find what the next direction is based on the travelling direction
        const auto localPosition = GridConversion::GridToChunkLocal(gridPosition, chunkManager->chunkSize);
        const auto& tile = grid->Get(localPosition, chunkManager->chunkSize);
        const auto nextDirection = Rail::GetNextTravellingDir(controller.travellingDirection, tile.railType);

        // don't find the next tile if its no rail.
        if (nextDirection != Rail::Dir::None)
        {
            // get the next tile
            const auto directionOffset = Rail::GetDirectionOffset(nextDirection);
            const auto offset = directionOffset + gridPosition;
            const auto nextPosition = GridConversion::GridToPixel(offset, chunkManager->cellSize);
            const auto offsetChunk = GridConversion::GridToChunk(offset, chunkManager->chunkSize);
            const auto offsetEntity = chunkManager->TryGetChunk(offsetChunk);

            if (const auto* offsetGrid = offsetEntity.TryGetComponent<Grid<RailTile>>())
            {
                const auto nextLocalPosition = GridConversion::GridToChunkLocal(offset, chunkManager->chunkSize);
                const auto& nextTile = offsetGrid->Get(nextLocalPosition, chunkManager->chunkSize);

                controller.lastPos = controller.nextPos;
                controller.currentTime = 0.0f;
                controller.travellingDirection = nextDirection;

                if (nextTile.railType != Rail::Type::None)
                {
                    controller.nextPos = nextPosition;
                    controller.nextRail = nextTile.railType;
                }
            }
        }
    }
}

void MineCarMovement::HandleTurning(Maize::Entity e, RailController& controller, const RailRotations& rotations)
{
    constexpr float turningPoint = 0.5f;
    const bool isTurningPoint = controller.currentTime >= turningPoint;

    static auto currentTurnRailType = Rail::Type::None;

    // is the next rail type a bend
    if (Rail::IsCurve(controller.nextRail))
    {
        if (isTurningPoint && !controller.isTurning)
        {
            controller.isTurning = true;
            currentTurnRailType = controller.nextRail;
        }
    }
    // has hit the next turning point
    else if (isTurningPoint && controller.isTurning)
    {
        controller.isTurning = false;
        controller.turningTime = 0.0f;
        currentTurnRailType = Rail::Type::None;

        if (auto* renderer = e.TryGetMutComponent<Maize::SpriteRenderer>())
        {
            renderer->sprite.SetTextureRect(rotations.GetRotationSprite(rotations.GetDirectionIndex(controller.travellingDirection)));
        }
    }

    if (controller.isTurning)
    {
        // normalise the turning time from [0.5f -> 0.5f] to [0.0f -> 1.0f]
        if (Rail::IsCurve(controller.nextRail)) controller.turningTime = controller.currentTime - 0.5f;
        else
        {
            controller.turningTime = controller.currentTime + 0.5f;
        }

        /*const uint8_t numberOfSprites = sprites.size();
        const uint8_t currentSprite = static_cast<uint8_t>(controller.turningTime * numberOfSprites);

        if (auto* renderer = e.TryGetMutComponent<Maize::SpriteRenderer>())
        {
            renderer->sprite.SetTextureRect(sprites[currentSprite]);
        }*/
    }
}
