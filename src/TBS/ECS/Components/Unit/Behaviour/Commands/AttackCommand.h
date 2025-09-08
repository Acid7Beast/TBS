// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseCommand.h"

#include <vector>

namespace acid7beast::tbs
{
	class AttackCommand : public BaseCommand
	{
		// Public interface methods.
	public:
		Status Execute(Registry& registry, WorldContext& worldContext, EntityId id) override;
	};
} // namespace acid7beast::tbs
