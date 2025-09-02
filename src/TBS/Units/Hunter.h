// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "Unit.h"

namespace acid7beast::tbs
{
	class Hunter final : public BaseUnit
	{
	public:
		Hunter(uint32_t unitId, const IVector2& position, int hp, int agility, int strength, int range);

	public:
		void Visit(UnitVisitor& visitor) override;
	};
} // namespace acid7beast::tbs
