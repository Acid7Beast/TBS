// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "../Common.h"
#include "IComponentStorage.h"

#include <vector>
#include <limits>

namespace acid7beast::tbs
{
	template<typename ComponentType>
	class ComponentStorage final : public IComponentStorage
	{
	public:
		inline ComponentStorage();

		// Public interface methods.
	public:
		inline void AddComponent(EntityId entity, ComponentType&& component);

		inline void RemoveComponent(EntityId entity) override;
		inline ComponentType* GetComponent(EntityId entity);
		inline std::vector<ComponentType>& GetDenseData() { return _denseArray; }
		inline const std::vector<ComponentType>& GetDenseData() const { return _denseArray; }
		inline const std::vector<EntityId>& GetEntityList() const { return _denseToEntity; }
		inline uint32_t Size() const { return _size; }

		// Private constants.
	private:
		static constexpr uint32_t kInvalid = std::numeric_limits<uint32_t>::max();

		// Private state members.
	private:
		std::vector<ComponentType> _denseArray;
		std::vector<EntityId> _denseToEntity;
		std::vector<uint32_t> _sparseArray;
		uint32_t _size;
	};

	template<typename ComponentType>
	inline ComponentStorage<ComponentType>::ComponentStorage()
		: _size { 0 }
	{}

	template<typename ComponentType>
	inline void ComponentStorage<ComponentType>::AddComponent(EntityId entity, ComponentType&& component)
	{
		if (entity >= _sparseArray.size()) {
			_sparseArray.resize(entity + 1, kInvalid);
		}

		uint32_t& const sparseIndex = _sparseArray[entity];

		// If the entity already has a component, replace it.
		if (sparseIndex != kInvalid && sparseIndex < _size && _denseToEntity[sparseIndex] == entity) {
			_denseArray[sparseIndex] = std::move(component);
			return;
		}

		// Add new component at the end of the dense array.
		if (_size < _denseArray.size()) {
			_denseArray[_size] = std::move(component);
			_denseToEntity[_size] = entity;
		}
		else {
			_denseArray.push_back(std::move(component));
			_denseToEntity.push_back(entity);
		}
		sparseIndex = _size;
		++_size;
	}

	template<typename ComponentType>
	inline void ComponentStorage<ComponentType>::RemoveComponent(EntityId entity)
	{
		if (entity >= _sparseArray.size()) {
			return;
		}

		uint32_t& const indexToRemove = _sparseArray[entity];
		if (indexToRemove == kInvalid || indexToRemove >= _size || _denseToEntity[indexToRemove] != entity) {
			return;
		}

		const uint32_t lastIndex = _size - 1;
		if (indexToRemove != lastIndex) {
			_denseArray[indexToRemove] = std::move(_denseArray[lastIndex]);
			_denseToEntity[indexToRemove] = _denseToEntity[lastIndex];
			_sparseArray[_denseToEntity[lastIndex]] = indexToRemove;
		}
		
		indexToRemove = kInvalid;
		--_size;
	}

	template<typename ComponentType>
	inline ComponentType* ComponentStorage<ComponentType>::GetComponent(EntityId entity)
	{
		if (entity >= _sparseArray.size()) {
			return nullptr;
		}

		const uint32_t sparseIndex = _sparseArray[entity];
		if (sparseIndex == kInvalid || sparseIndex >= _size || _denseToEntity[sparseIndex] != entity) {
			return nullptr;
		}
		return &_denseArray[sparseIndex];
	}
} // namespace acid7beast::tbs
