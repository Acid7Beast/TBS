// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/ECS/Components/Unit/Common.h>
#include <vector>

namespace acid7beast::tbs
{
	struct Durability
	{
		int durability;
		int maxDurability;
	};
	
	struct HealthComponent final
	{
		std::vector<Durability> durabilities;
	};
} // namespace acid7beast::tbs
