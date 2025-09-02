// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseAttackCommand.h"

namespace acid7beast::tbs
{
	class DistantAttackCommand final : public BaseAttackCommand
	{
	public:
		DistantAttackCommand();

	public:
		std::vector<Unit*> GetEnemies(WorldContext& worldContext, Unit& unit) const override;
	};
}  // namespace acid7beast::tbs
