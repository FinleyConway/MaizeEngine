#pragma once

#include <flecs.h>

#include "Maize/Core/Macros/Log.h"
#include "Maize/Scene/Components/Position.h"

namespace Maize {

	class Entity
	{
	public:
		constexpr Entity() = default;

		template<typename TComponent>
		bool AddComponent(TComponent&& component)
		{
			if (!HasComponent<TComponent>())
			{
				m_Handle.set<TComponent>(std::forward<TComponent>(component));

				return true;
			}

			CORE_LOG_WARN("Adding a component that is already on the entity!");

			return false;
		}

		template<typename TComponent>
		bool AddComponent() const
		{
			if (!HasComponent<TComponent>())
			{
				m_Handle.add<TComponent>();

				return true;
			}

			CORE_LOG_WARN("Adding a component that is already on the entity!");

			return false;
		}

		template<typename TComponent>
		TComponent& GetOrCreateComponent()
		{
			return m_Handle.ensure<TComponent>();
		}

		template<typename TComponent>
		const TComponent* TryGetComponent() const
		{
			return m_Handle.get<TComponent>();
		}

		template<typename TComponent>
		TComponent* TryGetMutComponent()
		{
			return m_Handle.get_mut<TComponent>();
		}

		template<typename TComponent>
		bool RemoveComponent()
		{
			if constexpr(std::is_same_v<TComponent, Position>)
			{
				CORE_LOG_WARN("Cannot remove Position component!");
				return false;
			}

			m_Handle.remove<TComponent>();

			return true;
		}

		template<typename TComponent>
		bool HasComponent() const
		{
			if (!IsNull())
			{
				return m_Handle.has<TComponent>();
			}

			return false;
		}

		bool IsNull() const
		{
			return m_Handle.is_alive() && m_Handle != flecs::entity::null();
		}

		uint32_t ID() const
		{
			return m_Handle.id();
		}

		std::string_view Name() const
		{
			return m_Handle.name().c_str();
		}

		void Enable() const
		{
			m_Handle.enable();
		}

		void Disable() const
		{
			m_Handle.disable();
		}

		void Destroy() const
		{
			m_Handle.destruct();
		}

	private:
		explicit Entity(flecs::entity handle) : m_Handle(handle) { }

		flecs::entity m_Handle = flecs::entity::null();
	};

} // Maize