#pragma once

#include <flecs.h>

#include "Maize/Scene/Components/Position.h"
#include "Maize/Scene/Components/Active.h"

namespace Maize
{
    /**
     * An object that contains various components
     */
    class Entity
    {
    public:
        Entity() = default;

        /**
         * Adds or replaces a component.
         * Must wait next frame for the component to be initialised before getting the component. e.g: \n
         * if (entity.HasComponent<TComponent>()) // will not be true until next frame
         * @tparam TComponent Component type.
         * @param component Component constructor parameters.
         * @return Returns true if it was added.
         */
        template<typename TComponent>
        bool AddComponent(TComponent&& component = TComponent{})
        {
            if (IsNull()) return false;

            // if TComponent is an empty type or has a default constructor
            if constexpr (std::is_empty_v<TComponent> && std::is_trivially_constructible_v<TComponent>)
            {
                m_Handle.add<TComponent>();
            }
            else
            {
                m_Handle.set<TComponent>(std::forward<TComponent>(component));
            }

            return true;
        }

        /**
         * Attempts to get the component.
         * @tparam TComponent Component type.
         * @return Returns a const TComponent or nullptr if the entity does not have the component.
         */
        template<typename TComponent>
        const TComponent* TryGetComponent() const
        {
            if (IsNull()) return nullptr;

            return m_Handle.get<TComponent>();
        }

        /**
         * Attempts to get the component.
         * @tparam TComponent Component type.
         * @return Returns a TComponent or nullptr if the entity does not have the component.
         */
        template<typename TComponent>
        TComponent* TryGetMutComponent()
        {
            if (IsNull()) return nullptr;

            // mark component as dirty (on set hooks)
            if (HasComponent<TComponent>()) m_Handle.modified<TComponent>();

            return m_Handle.get_mut<TComponent>();
        }

        /**
         * Removes the component.
         * @tparam TComponent Component type.
         * @return Returns true if it was successful or false if it attempts to remove an entity it does not have or a non-removable component.
         */
        template<typename TComponent>
        bool RemoveComponent()
        {
            if (!HasComponent<TComponent>()) return false;

            if constexpr (std::is_same_v<TComponent, Position>)
            {
                CORE_LOG_WARN("Cannot remove Position component!");
                return false;
            }

            if constexpr (std::is_same_v<TComponent, Active>)
            {
                CORE_LOG_WARN("Cannot remove Active component!");
                return false;
            }

            m_Handle.remove<TComponent>();

            return true;
        }

        /**
         * Checks if the entity has component.
         * @tparam TComponent Component type.
         * @return If it has the component or not.
         */
        template<typename TComponent>
        bool HasComponent() const
        {
            if (!IsNull())
            {
                return m_Handle.has<TComponent>();
            }

            return false;
        }

        /**
         * Is entity not alive or non-existent.
         */
        bool IsNull() const
        {
            return !m_Handle.is_alive() && m_Handle == flecs::entity::null();
        }

        /**
         * The entity id.
         */
        uint32_t ID() const
        {
            return m_Handle.id();
        }

        /**
         * Enables the entity, allow it to update.
         * @return Returns true if it was disabled successfully.
         */
        bool Enable() const
        {
            if (IsNull()) return false;

            m_Handle.enable();

            return true;
        }

        /**
         * Enable component, making that entity match with systems with expected component.
         * @tparam TComponent Component type.
         * @return Returns true if it has the component and was enabled.
         */
        template<typename TComponent>
        bool EnableComponent() const
        {
            if (HasComponent<TComponent>())
            {
                m_Handle.enable<TComponent>();

                return true;
            }

            return false;
        }

        /**
         * Disable the entity, prevent it from being updated.
         * @return Returns true if it was disabled successfully.
         */
        bool Disable() const
        {
            if (IsNull()) return false;

            m_Handle.disable();

            return true;
        }

        /**
         * Disable component, making that entity not match with systems with expected component.
         * @tparam TComponent Component type.
         * @return Returns true if it has the component and was disabled.
         */
        template<typename TComponent>
        bool DisableComponent() const
        {
            if constexpr (std::is_same_v<TComponent, Position>)
            {
                CORE_LOG_WARN("Cannot disable Position component!");
                return false;
            }

            if constexpr (std::is_same_v<TComponent, Active>)
            {
                CORE_LOG_WARN("Cannot disable Active component!");
                return false;
            }

            if (HasComponent<TComponent>())
            {
                m_Handle.disable<TComponent>();

                return true;
            }

            return false;
        }

        /**
         * Destroy the entity, remove it from the world entirely.
         * @return Returns true if it was destroyed successfully.
         */
        bool Destroy() const
        {
            if (IsNull()) return false;

            m_Handle.destruct();

            return true;
        }

    private:
        template<typename... Args>
        static Entity CreateEntity(flecs::world& world, Vec2f position, Args&&... args)
        {
            auto entity = Entity(world.entity());

            entity.AddComponent<Active>(); // tag that labels this entity as an active for easy removal
            entity.AddComponent(Position(position));
            (entity.AddComponent<Args>(std::forward<Args>(args)), ...); // add custom objects

            return entity;
        }

    private:
        friend class Scene;
        friend class SystemState;

        explicit Entity(flecs::entity handle) : m_Handle(handle)
        {
        }

        flecs::entity m_Handle = flecs::entity::null();
    };
} // Maize
