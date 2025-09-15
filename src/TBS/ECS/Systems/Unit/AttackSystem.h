// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/ECS/Components/Unit/Common.h>

namespace acid7beast::tbs
{
	class Registry;
	struct WorldContext;

	class AttackSystem final
	{
		// Public interface methods.
	public:
		void Update(Registry& registry, WorldContext& worldContext);
	};
} // namespace acid7beast::tbs
