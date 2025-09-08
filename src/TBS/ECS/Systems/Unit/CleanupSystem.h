// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/ECS/Common.h>

namespace acid7beast::tbs
{
	class WorldContext;

	class CleanupSystem final
	{
		// Public interface methods.
	public:
		void Update(Registry& registry, WorldContext& worldContext);
	};
} // namespace acid7beast::tbs