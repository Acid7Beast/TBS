// (c) 2025 Acid7Beast. Use with wisdom.

#include "Map.h"

#include <algorithm>
#include <iterator>
#include <ranges>

#include <TBS/ECS/Registry/Registry.h>
#include <TBS/ECS/Components/Unit/Movement/MovementComponent.h>

namespace acid7beast::tbs
{
	void Map::Create(const IVector2& size)
	{
		_width = size.x;
		_height = size.y;
		_cells.assign(_width * _height, std::vector<EntityId>());
	}

	bool Map::IsValidPosition(const IVector2& pos) const
	{
		return pos.x >= 0 && pos.x < _width && pos.y >= 0 && pos.y < _height;
	}

	bool Map::IsCellOccupied(const IVector2& pos) const
	{
		return IsValidPosition(pos) && !_cells[pos.y * _width + pos.x].empty();
	}

	void Map::PlaceEntity(EntityId id, const IVector2& pos)
	{
		if (IsValidPosition(pos)) {
			_cells[pos.y * _width + pos.x].push_back(id);
		}
	}

	void Map::RemoveEntity(EntityId id, const IVector2& pos)
	{
		if (IsValidPosition(pos)) {
			auto& cellEntities = _cells[pos.y * _width + pos.x];
			auto it = std::find(cellEntities.begin(), cellEntities.end(), id);
			if (it != cellEntities.end()) {
				cellEntities.erase(it);
			}
		}
	}

	std::vector<EntityId> Map::GetEntitiesInRadius(Registry& registry, const IVector2& pos, EntityId id, int minRadius, int maxRadius, DamageReachability reachability) const
	{
		std::unordered_set<EntityId> entitiesInMaxRadius = GetEntitiesInRadius(registry, pos, maxRadius, reachability);
		std::unordered_set<EntityId> entitiesInMinRadius = GetEntitiesInRadius(registry, pos, minRadius, reachability);

		auto entitiesInRadiusView = entitiesInMaxRadius
							 | std::views::filter([&entitiesInMinRadius](EntityId eid) { return !entitiesInMinRadius.contains(eid); })
							 | std::views::filter([id](EntityId enemyId) { return id != enemyId; });

		return { entitiesInRadiusView.begin(), entitiesInRadiusView.end() };
	}

	std::unordered_set<EntityId> Map::GetEntitiesInRadius(Registry& registry, const IVector2& pos, int radius, DamageReachability reachability) const
	{
		std::unordered_set<EntityId> entitiesInRadius;
		for (int dy = -radius; dy <= radius; ++dy) {
			for (int dx = -radius; dx <= radius; ++dx) {
				const IVector2 targetPos = { pos.x + dx, pos.y + dy };

				const int coneBorderDistance = radius - std::max(std::abs(dx), std::abs(dy));

				if (!IsValidPosition(targetPos)) {
					continue;
				}

				const auto& cellEntities = _cells[targetPos.y * _width + targetPos.x];
				for (int eid : cellEntities) {
					auto* movementComponent = registry.GetComponent<MovementComponent>(eid);
					if (movementComponent == nullptr) {
						continue;
					}

					if (reachability == DamageReachability::Melee && movementComponent->GetTravelMethod() != TravelMethod::Ground) {
						continue;
					}

					if (movementComponent->GetGroundDistance() <= coneBorderDistance) {
						entitiesInRadius.insert(eid);
					}
				}
			}
		}

		return entitiesInRadius;
	}
} // namespace acid7beast::tbs
