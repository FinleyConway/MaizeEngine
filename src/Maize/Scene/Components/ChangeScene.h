#pragma once

namespace Maize
{
    class Scene;

    struct ChangeScene
    {
        std::unique_ptr<Scene> newScene;
    };
} // Maize