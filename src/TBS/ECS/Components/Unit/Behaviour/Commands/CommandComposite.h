// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseCommand.h"

#include <memory>
#include <vector>

namespace acid7beast::tbs
{
	class Registry;

	class CommandComposite final : public BaseCommand
	{
		// Public interface methods.
	public:
		void AddCommand(std::unique_ptr<BaseCommand> command);
		void Pend(Registry& registry, WorldContext& worldContext, EntityId id) override;
		Status Execute(Registry& registry, WorldContext& worldContext, EntityId id) override;

		// Private state members.
	private:
		std::vector<std::unique_ptr<BaseCommand>> _commands {};
	};
} // namespace acid7beast::tbs
