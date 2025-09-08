// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/System/EntityFactory.h>
#include <TBS/System/WorldContext.h>
#include <TBS/ECS/Components/Unit/Behaviour/BehaviourComponent.h>
#include <TBS/ECS/Components/Unit/Movement/MovementComponent.h>
#include <TBS/ECS/Components/Unit/Health/HealthComponent.h>
#include <TBS/ECS/Components/Unit/Attack/AttackComponent.h>

#include <IO/Commands/SpawnHunter.hpp>

namespace acid7beast::tbs
{
	// New entity-based specialization
	template<>
	inline void EntityFactory<sw::io::SpawnHunter>::SpawnEntity(Registry& registry, WorldContext& worldContext)
	{
		const IVector2& position = IVector2 { _params.x, _params.y };
		if (worldContext.map.IsCellOccupied(position)) {
			throw std::runtime_error("Cell is occupied");
			return;
		}

		Durability health = { _params.hp, _params.hp };
		Weapon sword = { 1, 1, _params.strength, DamageReachability::Melee };
		Weapon bow = { 2, _params.range, _params.agility, DamageReachability::Distant };

		const uint32_t id = registry.CreateEntity(_params.unitId);
		registry.AddComponent(id, MovementComponent { position });
		registry.AddComponent(id, BehaviourComponent {});
		registry.AddComponent(id, HealthComponent { { std::move(health) } });
		registry.AddComponent(id, AttackComponent { { std::move(sword), std::move(bow) } });

		worldContext.map.PlaceEntity(id, position);
		worldContext.logger.LogEntitySpawned(worldContext.tick, _params.unitId, _params.Name, position);
		worldContext.turnOrder.push_back(id);
	}
} // namespace acid7beast::tbs
