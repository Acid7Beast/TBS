// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Common.h>
#include <TBS/ECS/Components/Unit/Common.h>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace acid7beast::tbs
{
	class Registry;

	class Map final
	{
		// Public interface methods.
	public:
		void Create(const IVector2& size);
		bool IsValidPosition(const IVector2& pos) const;
		bool IsCellOccupied(const IVector2& pos) const;
		void PlaceEntity(EntityId id, const IVector2& pos);
		void RemoveEntity(EntityId id, const IVector2& pos);
		std::vector<EntityId> GetEntitiesInRadius(Registry& registry, const IVector2& pos, EntityId id, int minRadius, int maxRadius, DamageReachability reachability) const;

		// Private helpers.
	private:
		std::unordered_set<EntityId> GetEntitiesInRadius(Registry& registry, const IVector2& pos, int radius, DamageReachability reachability) const;

		// Private state members.
	private:
		uint32_t _width = 0, _height = 0;
		std::vector<std::vector<uint32_t>> _cells;
	};
} // namespace acid7beast::tbs
