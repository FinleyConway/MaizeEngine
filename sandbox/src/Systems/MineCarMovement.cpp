#include "MineCarMovement.h"

#include "Components/ChunkManager.h"
#include "Components/RailController.h"
#include "Utils/GridConversion.h"
#include "Utils/Rail.h"

void MineCarMovement::Move(Maize::SystemState s, Maize::Position& position, RailController& controller)
{
    auto* input = s.GetSingleton<Maize::Input>();
    const auto* chunkManager = s.GetSingleton<ChunkManager>();

    GAME_ASSERT(chunkManager != nullptr, "ChunkManager is nullptr");

    ImGui::Begin("Mine Car Stats");
    ImGui::Text("Speed: %f", controller.speed);
    ImGui::Text("Current Dir: %s", Rail::DirToStr(controller.travellingDirection).data());
    ImGui::Text("Next Dir: %s", Rail::DirToStr(controller.nextDirection).data());
    ImGui::Text("Is Turning: %s", controller.isTurning ? "Turning" : "Not Turning");
    ImGui::Text("Current Time To Next: %f", controller.currentTime);
    ImGui::Text("Current Position: %s", position.ToString().data());
    ImGui::Text("Last Position: %s", controller.lastPos.ToString().data());
    ImGui::Text("Next Position: %s", controller.nextPos.ToString().data());
    ImGui::Text("Next Direction: %s", Rail::TypeToStr(controller.nextRail).data());
    ImGui::Text("Turning Time: %f", controller.turningTime);
    ImGui::End();

    if (input->GetButtonHeld(Maize::KeyCode::W))
    {
        if (controller.travellingDirection == Rail::Dir::N || controller.travellingDirection == Rail::Dir::S)
        {
            if (input->GetButtonHeld(Maize::KeyCode::A)) controller.nextDirection = Rail::Dir::W;
            else if (input->GetButtonHeld(Maize::KeyCode::D)) controller.nextDirection = Rail::Dir::E;
            else controller.nextDirection = controller.travellingDirection;
        }
        else if (controller.travellingDirection == Rail::Dir::W)
        {
            if (input->GetButtonHeld(Maize::KeyCode::A)) controller.nextDirection = Rail::Dir::S;
            else if (input->GetButtonHeld(Maize::KeyCode::D)) controller.nextDirection = Rail::Dir::N;
            else controller.nextDirection = controller.travellingDirection;
        }
        else
        {
            if (input->GetButtonHeld(Maize::KeyCode::A)) controller.nextDirection = Rail::Dir::N;
            else if (input->GetButtonHeld(Maize::KeyCode::D)) controller.nextDirection = Rail::Dir::S;
            else controller.nextDirection = controller.travellingDirection;
        }

        HandleMovement(s, position, controller, chunkManager);
    }
    else
    {
        controller.isMoving = false;
    }
}

void MineCarMovement::HandleMovement(Maize::SystemState s, Maize::Position& position, RailController& controller, const ChunkManager* chunkManager)
{
    const bool canTravelTo = Rail::CanDirToType(controller.travellingDirection, controller.nextRail);
    const bool atDestination = position.ApproxOf(controller.nextPos);

    // try to move to the next rail when travelled to the next position.
    if (atDestination)
    {
        controller.isMoving = false;
        HandleDirection(chunkManager, controller);
    }
    // move controller
    else if (canTravelTo && Rail::GetNextTravellingDir(controller.travellingDirection, controller.nextDirection, controller.nextRail) != Rail::Dir::None)
    {
        controller.isMoving = true;
        controller.currentTime += controller.speed * s.DeltaTime();
        controller.currentTime = std::clamp(controller.currentTime, 0.0f, 1.0f);

        position = controller.lastPos.LerpTo(controller.nextPos, controller.currentTime);

    }
    // keep checking if there is a next rail when there is no rail ahead.
    else
    {
        controller.isMoving = false;
        HandleDirection(chunkManager, controller);
    }
}

void MineCarMovement::HandleDirection(const ChunkManager* chunkManager, RailController& controller)
{
    const auto gridPosition = GridConversion::PixelToGrid(controller.nextPos, chunkManager->cellSize);
    const auto chunkPosition = GridConversion::GridToChunk(gridPosition, chunkManager->chunkSize);
    const auto entity = chunkManager->TryGetChunk(chunkPosition);

    // check if the grid exists and get the next rail.
    if (const auto* grid = entity.TryGetComponent<Grid<RailTile>>())
    {
        HandleNextRail(grid, gridPosition, chunkManager, controller);
    }
}

void MineCarMovement::HandleNextRail(const Grid<RailTile>* grid, Maize::Vec2i gridPosition, const ChunkManager* chunkManager, RailController& controller)
{
    const auto localPosition = GridConversion::GridToChunkLocal(gridPosition, chunkManager->chunkSize);
    const auto& tile = grid->Get(localPosition, chunkManager->chunkSize);
    const auto nextDirection = Rail::GetNextTravellingDir(controller.travellingDirection, controller.nextDirection, tile.railType);

    // assign a next rail if there is no rail ahead assigned.
    if (controller.nextRail == Rail::Type::None)
    {
        controller.nextRail = tile.railType;
    }
    // update controller next positions
    else
    {
        UpdateRailPosition(gridPosition, nextDirection, chunkManager, controller);
    }
}

void MineCarMovement::UpdateRailPosition(Maize::Vec2i gridPosition, Rail::Dir nextDirection, const ChunkManager* chunkManager, RailController& controller)
{
    const auto directionOffset = Rail::GetDirectionOffset(nextDirection);
    const auto offset = directionOffset + gridPosition;
    const auto nextPosition = GridConversion::GridToPixel(offset, chunkManager->cellSize);
    const auto offsetChunk = GridConversion::GridToChunk(offset, chunkManager->chunkSize);
    const auto offsetEntity = chunkManager->TryGetChunk(offsetChunk);

    if (const auto* offsetGrid = offsetEntity.TryGetComponent<Grid<RailTile>>())
    {
        const auto nextLocalPosition = GridConversion::GridToChunkLocal(offset, chunkManager->chunkSize);
        const auto& nextTile = offsetGrid->Get(nextLocalPosition, chunkManager->chunkSize);

        if (Rail::CanDirToType(nextDirection, nextTile.railType))
        {
            controller.lastPos = controller.nextPos;
            controller.currentTime = 0.0f;
            controller.travellingDirection = nextDirection;
            controller.nextRail = nextTile.railType;
            controller.nextPos = nextPosition;
        }
    }
}
