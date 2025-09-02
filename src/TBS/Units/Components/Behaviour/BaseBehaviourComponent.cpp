// (c) 2025 Acid7Beast. Use with wisdom.

#include "BaseBehaviourComponent.h"

#include <TBS/World/WorldContext.h>
#include <TBS/Units/Unit.h>

namespace acid7beast::tbs
{
	ActingState BaseBehaviourComponent::Act(WorldContext& worldContext)
	{
		if (_owner == nullptr) {
			return ActingState::Inactive;
		}

		// Execute commands in order until one succeeds or all fail.
		while (!_commands.empty()) {
			std::unique_ptr<BaseCommand>& command = _commands.front();
			if (command == nullptr) {
				_commands.pop_front();
				continue;
			}

			const BaseCommand::Status status = command->Execute(worldContext, *_owner);
			if (status == BaseCommand::Status::Success) {
				return ActingState::Actioning;
			}

			_commands.pop_front();
		}

		return ActingState::Inactive;
	}
} // namespace acid7beast::tbs
