#include "MineCarRotate.h"

#include "Components/RailController.h"
#include "Components/RailRotations.h"

void MineCarRotate::Rotate(Maize::SystemState s, Maize::Entity e, Maize::SpriteRenderer& spriteRenderer,
    RailController& controller, const RailRotations& rotations)
{
    // handle on turn state
    OnTurnStart(controller, rotations);

    // handle on end turn state
    OnTurnEnd(controller);

    // handle turning state
    OnTurn(s, spriteRenderer, controller);
}

void MineCarRotate::OnTurnStart(RailController& controller, const RailRotations& rotations)
{
    constexpr float turningPoint = 0.5f;
    const bool isTurningPoint = controller.currentTime >= turningPoint;
    const auto nextDir = Rail::GetNextTravellingDir(controller.travellingDirection, controller.nextRail);
    const bool isTurn = nextDir != controller.travellingDirection;

    // if the controller is about to turn
    if (isTurn && isTurningPoint && !controller.isTurning)
    {
        // get the appropriate turn
        if (const auto* turnDirection = GetTurnDirection(controller, rotations))
        {
            controller.currentRotations = turnDirection;
            controller.currentRotateDirection = controller.travellingDirection;
            controller.isTurning = true;
        }
    }
}

void MineCarRotate::OnTurn(Maize::SystemState s, Maize::SpriteRenderer& spriteRenderer, RailController& controller)
{
    if (controller.isTurning && controller.isMoving)
    {
        controller.turningTime += controller.speed * s.DeltaTime();
        controller.turningTime = std::clamp(controller.turningTime, 0.0f, 1.0f);

        const uint8_t numberOfSprites = controller.currentRotations->GetNumberOfRotations();
        const uint8_t currentSprite = std::round(controller.turningTime * numberOfSprites);
        const auto& rect = controller.currentRotations->GetRotation(controller.currentRotateDirection, currentSprite);

        spriteRenderer.sprite.SetTextureRect(rect);
    }
}

void MineCarRotate::OnTurnEnd(RailController& controller)
{
    const bool isTurnEnd = controller.turningTime >= 1.0f && controller.isTurning;

    if (isTurnEnd)
    {
        controller.isTurning = false;
        controller.currentRotations = nullptr;
        controller.turningTime = 0.0f;
    }
}

const RailTurnDirection* MineCarRotate::GetTurnDirection(const RailController& controller, const RailRotations& rotations)
{
    for (const auto& rotation : rotations.rotations)
    {
        if (rotation.DoesMatchDirection(controller.travellingDirection, controller.nextRail))
        {
            return &rotation; // this should be safe as im not expecting to resize the vector during runtime.
        }
    }

    return nullptr;
}
