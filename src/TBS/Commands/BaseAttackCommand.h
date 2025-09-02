// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseCommand.h"

#include <TBS/Units/Unit.h>
#include <vector>

namespace acid7beast::tbs
{
	class BaseAttackCommand : public BaseCommand
	{
	public:
		BaseAttackCommand(DamageReachability reachability);

	public:
		Status Execute(WorldContext& worldContext, Unit& unit) override;

	protected:
		virtual std::vector<Unit*> GetEnemies(WorldContext& worldContext, Unit& unit) const = 0;

	protected:
		DamageReachability _reachability;
	};
} // namespace acid7beast::tbs
