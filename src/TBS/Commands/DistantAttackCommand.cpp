// (c) 2025 Acid7Beast. Use with wisdom.

#include "DistantAttackCommand.h"

#include <TBS/World/WorldContext.h>

namespace acid7beast::tbs
{
	DistantAttackCommand::DistantAttackCommand()
		: BaseAttackCommand(DamageReachability::Distant)
	{}

	std::vector<Unit*> DistantAttackCommand::GetEnemies(WorldContext& worldContext, Unit& unit) const
	{
		return worldContext.map.GetUnitInRadius(worldContext.units, unit.Movement().GetPosition(), 2, unit.Attack().GetAttackDistance() + 1);
	}
} // namespace acid7beast::tbs
