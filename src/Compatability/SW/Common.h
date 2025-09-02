// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Common.h>

namespace acid7beast::tbs
{
	template<typename CommandParams>
	IVector2 GetMapSize(const CommandParams& params)
	{
		return { params.width, params.height };
	}

	template<typename CommandParams>
	uint32_t GetUnitId(const CommandParams& params)
	{
		return params.unitId;
	}
} // namespace acid7beast::tbs
