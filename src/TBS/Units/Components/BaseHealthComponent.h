// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "Common.h"

namespace acid7beast::tbs
{
	class BaseUnit;
	struct WorldContext;

	class BaseHealthComponent
	{
	public:
		BaseHealthComponent(BaseUnit& unit);

	public:
		virtual uint32_t GetHealth() const = 0;
		DamageState AcceptAttack(WorldContext& worldContext, int damage, DamageReachability reachability);
		
		protected:
		virtual DamageState TakeAndTestDamage(int damage) = 0;

	protected:
		BaseUnit& _unit;
	};
} // namespace acid7beast::tbs
