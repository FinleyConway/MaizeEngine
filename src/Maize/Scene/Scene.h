#pragma once

#include "Maize/Scene/SystemState.h"
#include "Maize/Scene/Entity.h"
#include "Maize/Math/Vec2.h"

namespace Maize
{
    namespace Internal
    {
        class SceneManager;
    } // Internal

    /**
     * A world where all the entities and game data lives.
     */
    class Scene
    {
    public:
        Scene() = default;

        virtual ~Scene() = default;

        /**
         * A function that is called when the scene starts which is where all systems and entities are created.
         */
        virtual void OnStart() = 0;

        /**
         * A function that is called when the scene ends which where all necessary clean up happens.
         */
        virtual void OnEnd() = 0;

    protected:
        /**
         * Create an entity.
         * @tparam Args Various components that can be added.
         * @param position World location.
         * @param args Various components parameters.
         * @return The entity.
         */
        template<typename... Args>
        Entity CreateEntity(Vec2f position, Args&&... args) const
        {
            CORE_ASSERT(m_World != nullptr, "World has not been assigned!")

            return Entity::CreateEntity(*m_World, position, args...);
        }

        /**
         * Added a singleton the scene.
         * @tparam T The singleton type.
         */
        template<typename T>
        void CreateSingleton()
        {
            CORE_ASSERT(m_World != nullptr, "World has not been assigned!")

            flecs::entity e(m_World->c_ptr(), m_World->id<T>());
            e.add<T>();

            m_Singletons.emplace_back(e);
        }

        /**
         * Added a singleton the scene.
         * @tparam T The singleton type.
         * @param args The singleton parameters.
         */
        template<typename T, typename... Args>
        void CreateSingleton(Args&&... args)
        {
            CORE_ASSERT(m_World != nullptr, "World has not been assigned!")

            flecs::entity e(m_World->c_ptr(), m_World->id<T>());
            e.set(T(std::forward<Args>(args)...));

            m_Singletons.emplace_back(e);
        }

        /**
         * Add a system that will provide entities logic.
         * @tparam Components What components the system will work on.
         * @tparam Func The function that provides the logic with the components as the parameters.
         * @param systemName The name of the system.
         * @param updateOrder When will the system be updated.
         * @param systemFunc The function that provides the logic with the components as the parameters.
         * @return The system handle.
         */
        template<typename... Components, typename Func>
        flecs::system AddSystem(const std::string& systemName, flecs::entity_t updateOrder, Func&& systemFunc)
        {
            PROFILE_FUNCTION();

            CORE_ASSERT(m_World != nullptr, "World has not been assigned!");

            // Create system
            const flecs::system system = m_World->system<Components...>(systemName.c_str()).kind(updateOrder).each(
            [&, systemName](flecs::entity e, Components&... components)
            {
                PROFILE_SCOPE(systemName);

                // allow for optional SystemState and Entity
                if constexpr (std::is_invocable_v<Func, SystemState, Entity, Components&...>)
                {
                    systemFunc(SystemState(*m_World), Entity(e), components...);
                }
                else if constexpr (std::is_invocable_v<Func, SystemState, Components&...>)
                {
                    systemFunc(SystemState(*m_World), components...);
                }
                else if constexpr (std::is_invocable_v<Func, Entity, Components&...>)
                {
                    systemFunc(Entity(e), components...);
                }
                else
                {
                    systemFunc(components...);
                }

                // flag components that have been accessed that are not constant (on set hooks).
                ((std::is_const_v<Components> ? void() : e.modified<Components>()), ...);
            });

            m_Systems.emplace_back(system);

            return system;
        }

    private:
        void Initialise(flecs::world& world)
        {
            PROFILE_FUNCTION();

            m_World = &world;

            OnStart();

            // enable all systems for this scene
            for (const auto system : m_Systems)
            {
                system.enable();
            }

            // enable all observers for this scene
            for (const auto observer : m_Observers)
            {
                observer.enable();
            }
        }

        void Shutdown()
        {
            PROFILE_FUNCTION();

            OnEnd();

            // remove all non-persistent entities from the scene
            m_World->delete_with<Active>();

            // disable all systems for this scene
            for (const auto system : m_Systems)
            {
                system.disable();
            }

            // disable all observers for this scene
            for (const auto observer : m_Observers)
            {
                observer.disable();
            }

            // remove all singletons
            for (const auto entity : m_Singletons)
            {
                entity.clear();
            }
        }

    private:
        friend class Internal::SceneManager;

        flecs::world* m_World = nullptr;
        std::vector<flecs::system> m_Systems;
        std::vector<flecs::observer> m_Observers;
        std::vector<flecs::entity> m_Singletons;
    };
} // Maize
