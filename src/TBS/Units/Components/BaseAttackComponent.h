// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "Common.h"

namespace acid7beast::tbs
{
	class BaseAttackComponent
	{
	public:
		virtual uint32_t GetAttackDamage(DamageReachability reachability) const = 0;
		virtual uint32_t GetAttackDistance() const = 0;
	};
} // namespace acid7beast::tbs
