// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Common.h>
#include <TBS/ECS/Components/ComponentStorage.h>
#include <TBS/ECS/Components/IComponentStorage.h>

#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <optional>

namespace acid7beast::tbs
{
	class Registry final
	{
		// Public interface methods.
	public:
		EntityId CreateEntity(std::optional<EntityId> entityId = std::nullopt);
		void DestroyEntity(EntityId entity);

		template<typename T>
		inline void AddComponent(EntityId entity, T&& component);

		template<typename T>
		inline void RemoveComponent(EntityId entity);

		template<typename T>
		inline T* GetComponent(EntityId entity);

		template<typename T>
		inline ComponentStorage<T>& GetStorage();

		// Private state members.
	private:
		EntityId _nextEntityId = 0;
		std::vector<EntityId> _freeEntityIds;
		std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> _storages;
	};

	template<typename T>
	inline void Registry::AddComponent(EntityId entity, T&& component)
	{
		GetStorage<T>().AddComponent(entity, std::move(component));
	}

	template<typename T>
	inline void Registry::RemoveComponent(EntityId entity)
	{
		GetStorage<T>().RemoveComponent(entity);
	}

	template<typename T>
	inline T* Registry::GetComponent(EntityId entity)
	{
		return GetStorage<T>().GetComponent(entity);
	}

	template<typename T>
	inline ComponentStorage<T>& Registry::GetStorage()
	{
		if (_storages.find(std::type_index(typeid(T))) == _storages.end()) {
			_storages.emplace(std::type_index(typeid(T)), std::make_unique<ComponentStorage<T>>());
		}

		return *static_cast<ComponentStorage<T>*>(_storages.at(std::type_index(typeid(T))).get());
	}
} // namespace acid7beast::tbs
