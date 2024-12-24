#pragma once

namespace Maize
{
    class Scene;

    struct Active
    {
    };

    struct Persistent
    {
    };

    struct Static
    {
    };

    struct ChangeScene
    {
        std::unique_ptr<Scene> newScene;
    };
} // Maize
