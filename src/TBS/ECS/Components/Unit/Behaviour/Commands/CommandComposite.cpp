// (c) 2025 Acid7Beast. Use with wisdom.

#include "CommandComposite.h"

#include <TBS/ECS/Registry/Registry.h>

namespace acid7beast::tbs
{
	void CommandComposite::AddCommand(std::unique_ptr<BaseCommand> command)
	{
		_commands.push_back(std::move(command));
	}

	void CommandComposite::Pend(Registry& registry, WorldContext& worldContext, EntityId id)
	{
		for (const auto& command : _commands) {
			command->Pend(registry, worldContext, id);
		}
	}

	BaseCommand::Status CommandComposite::Execute(Registry& registry, WorldContext& worldContext, EntityId id)
	{
		for (const auto& command : _commands) {
			const Status status = command->Execute(registry, worldContext, id);
			if (status == Status::Success) {
				return Status::Success;
			}
		}

		return Status::Fail;
	}
} // namespace acid7beast::tbs
