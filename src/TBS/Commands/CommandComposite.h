// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseCommand.h"

#include <memory>
#include <vector>

namespace acid7beast::tbs
{
	class CommandComposite final : public BaseCommand
	{
	public:
		void AddCommand(std::unique_ptr<BaseCommand> command);

	public:
		void Pend(WorldContext& worldContext, Unit& unit) override;
		Status Execute(WorldContext& worldContext, Unit& unit) override;

	private:
		std::vector<std::unique_ptr<BaseCommand>> _commands {};
	};
} // namespace acid7beast::tbs
