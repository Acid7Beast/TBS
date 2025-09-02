// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "Map.h"
#include "../Common.h"

#include <TBS/Units/Unit.h>
#include <TBS/System/EventLogger.h>

namespace acid7beast::tbs
{
	struct WorldContext
	{
		BaseEventLogger& logger;
		uint64_t tick = 1;
		Map map;
		UnitTable units;
	};
} // namespace acid7beast::tbs
