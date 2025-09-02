// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseCommand.h"
#include "../Common.h"

namespace acid7beast::tbs
{
	class MoveCommand final : public BaseCommand
	{
	public:
		MoveCommand(const IVector2& targetPosition);

	public:
		void Pend(WorldContext& worldContext, Unit& unit) override;
		Status Execute(WorldContext& worldContext, Unit& unit) override;

	private:
		IVector2 _targetPosition;
	};
} // namespace acid7beast::tbs
