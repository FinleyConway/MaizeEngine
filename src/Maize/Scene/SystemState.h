#pragma once

#include "Maize/Scene/Entity.h"

namespace Maize {

	/**
	 * Utility tools for when handling logic within the system.
	 */
	class SystemState
	{
	public:
		/**
		 * Create an entity.
		 * @tparam Args Various components that can be added.
		 * @param position World location.
		 * @param isStatic Is the entity not movable?
		 * @param isPersistent Want to exist across scenes?
		 * @param args Various components parameters.
		 * @return The entity.
		 */
		template<typename... Args>
		Entity CreateEntity(Vec2f position, bool isStatic, bool isPersistent, Args&&... args) const
		{
			return Entity::CreateEntity(m_World, position, isStatic, isPersistent, args...);
		}

		/**
		 * Get persistent components.
		 * @tparam TSingleton Component type.
		 * @return Returns the persistent component or nullptr if type is not found.
		 */
		template<typename TSingleton>
		TSingleton* GetSingleton()
		{
			return m_World.get<TSingleton>();
		}

		/**
		 * The interval in seconds from the last frame to the current one.
		 */
		float DeltaTime() const
		{
			return m_World.delta_time();
		}

	private:
		friend class Scene;

		constexpr explicit SystemState(flecs::world& world) : m_World(world) { }

		flecs::world& m_World;
	};

} // Maize