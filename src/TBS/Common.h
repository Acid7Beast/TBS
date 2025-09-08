// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <stdint.h>
#include <unordered_map>
#include <memory>

namespace acid7beast::tbs
{
	using EntityId = uint32_t;
	
	struct IVector2
	{
		int32_t x;
		int32_t y;

		IVector2(uint32_t _x, uint32_t _y)
			: x { static_cast<int32_t>(_x) }
			, y { static_cast<int32_t>(_y) }
		{
		}

		IVector2(int32_t _x, int32_t _y)
			: x { _x }
			, y { _y }
		{
		}

		inline bool operator==(const IVector2& other) const { return x == other.x && y == other.y; }
		inline IVector2 operator-(const IVector2& other) const { return { x - other.x, y - other.y }; }
	};
} // namespace acid7beast::tbs
