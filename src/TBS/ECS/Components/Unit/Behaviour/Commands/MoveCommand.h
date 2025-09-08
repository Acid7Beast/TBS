// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseCommand.h"

#include <TBS/Common.h>

namespace acid7beast::tbs
{
	class MoveCommand final : public BaseCommand
	{
		// Life-circle management.
	public:
		MoveCommand(const IVector2& targetPosition);

		// Public interface methods.
	public:
		void Pend(Registry& registry, WorldContext& worldContext, EntityId id) override;
		Status Execute(Registry& registry, WorldContext& worldContext, EntityId id) override;

		// Private state members.
	private:
		IVector2 _targetPosition;
	};
} // namespace acid7beast::tbs
