// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "../Common.h"

#include <TBS/ECS/Registry/World/Map.h>
#include <TBS/ECS/Events/EventBus.h>
#include <TBS/System/EventLogger.h>
#include <vector>

namespace acid7beast::tbs
{
	struct WorldContext
	{
		BaseEventLogger& logger;
		uint64_t tick = 1;
		Map map;
		EventBus eventBus;
		std::vector<EntityId> turnOrder;
	};
} // namespace acid7beast::tbs
