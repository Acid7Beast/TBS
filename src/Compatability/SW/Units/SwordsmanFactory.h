// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Units/UnitFactory.h>
#include <TBS/Units/Components/Behaviour/SwordsmanBehaviourComponent.h>
#include <TBS/Units/Components/Movement/InfantryMovementComponent.h>
#include <TBS/Units/Components/Health/InfantryHealthComponent.h>
#include <TBS/Units/Components/Attack/MeleeAttackComponent.h>

#include <IO/Commands/SpawnSwordsman.hpp>

namespace acid7beast::tbs
{
	template<>
	inline void UnitFactory<sw::io::SpawnSwordsman>::SpawnUnit(WorldContext& worldContext)
	{
		std::unique_ptr<BaseBehaviourComponent> behaviourComponent = std::make_unique<SwordsmanBehaviourComponent>();
		std::unique_ptr<BaseMovementComponent> movementComponent = std::make_unique<InfantryMovementComponent>(IVector2 { _params.x, _params.y });
		std::unique_ptr<BaseHealthComponent> healthComponent = std::make_unique<InfantryHealthComponent>(_params.hp);
		std::unique_ptr<BaseAttackComponent> attackComponent = std::make_unique<MeleeAttackComponent>(_params.strength);
		
		std::unique_ptr<Unit> unit = std::make_unique<Unit>(_params.unitId, std::move(behaviourComponent), std::move(movementComponent), std::move(healthComponent), std::move(attackComponent));

		const IVector2& position = unit->Movement().GetPosition();
		if (worldContext.map.IsCellOccupied(position)) {
			throw std::runtime_error("Cell is occupied");
			return;
		}

		const uint32_t unitId = unit->GetId();
		worldContext.units.emplace(unitId, std::move(unit));
		worldContext.map.PlaceUnit(unitId, position);
		worldContext.logger.LogUnitSpawned(worldContext.tick, _params.unitId, _params.Name, position);
	}
} // namespace acid7beast::tbs
