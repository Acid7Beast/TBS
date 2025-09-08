// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <stdint.h>

namespace acid7beast::tbs
{
	enum class ActingState : uint8_t
	{
		Inactive = 0,
		Actioning,
		Dead,
	};

	enum class DamageReachability : uint8_t
	{
		Melee = 0,
		Distant
	};

	enum class TravelMethod : uint8_t
	{
		Ground,
		Air
	};

	enum class DamageState : uint8_t
	{
		Bearable = 0,
		Lethal,
	};
} // namespace acid7beast::tbs
