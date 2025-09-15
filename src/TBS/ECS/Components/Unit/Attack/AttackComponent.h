// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/ECS/Components/Unit/Common.h>

#include <vector>

namespace acid7beast::tbs
{
	struct Weapon
	{
		int startRange;
		int endRange;
		int damage;
		DamageReachability reachability;
	};

	struct AttackComponent final
	{
		std::vector<Weapon> weapons;
	};
} // namespace acid7beast::tbs
