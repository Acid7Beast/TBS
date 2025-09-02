// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "Unit.h"

namespace acid7beast::tbs
{
	class Swordsman final : public BaseUnit
	{
	public:
		Swordsman(uint32_t unitId, const IVector2& position, int hp, int strength);

	public:
		void Visit(UnitVisitor& visitor);
	};
} // namespace acid7beast::tbs
