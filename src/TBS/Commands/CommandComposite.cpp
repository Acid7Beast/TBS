// (c) 2025 Acid7Beast. Use with wisdom.

#include "CommandComposite.h"

#include <numeric>

namespace acid7beast::tbs
{
	void CommandComposite::AddCommand(std::unique_ptr<BaseCommand> command)
	{
		_commands.push_back(std::move(command));
	}

	void CommandComposite::Pend(WorldContext& worldContext, Unit& unit)
	{
		for (const auto& command : _commands) {
			command->Pend(worldContext, unit);
		}
	}

	BaseCommand::Status CommandComposite::Execute(WorldContext& worldContext, Unit& unit)
	{
		for (const auto& command : _commands) {
			const Status status = command->Execute(worldContext, unit);
			if (status == Status::Success) {
				return Status::Success;
			}
		}

		return Status::Fail;
	}
} // namespace acid7beast::tbs
