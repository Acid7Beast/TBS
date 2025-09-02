// (c) 2025 Acid7Beast. Use with wisdom.

#include "MeleeAttackCommand.h"

#include <TBS/World/WorldContext.h>

namespace acid7beast::tbs
{
	MeleeAttackCommand::MeleeAttackCommand()
		: BaseAttackCommand { DamageReachability::Melee }
	{}

	std::vector<Unit*> MeleeAttackCommand::GetEnemies(WorldContext& worldContext, Unit& unit) const
	{
		return worldContext.map.GetUnitInRadius(worldContext.units, unit.Movement().GetPosition(), 0, 1);
	}
} // namespace acid7beast::tbs
