// (c) 2025 Acid7Beast. Use with wisdom.

#include "BehaviourComponent.h"

#include <TBS/ECS/Registry/Registry.h>
#include <TBS/System/WorldContext.h>

namespace acid7beast::tbs
{
	BehaviourComponent::BehaviourComponent() = default;

	BehaviourComponent::BehaviourComponent(BehaviourComponent&& other) noexcept
		: _commands(std::move(other._commands))
	{}

	BehaviourComponent& BehaviourComponent::operator=(BehaviourComponent&& other) noexcept
	{
		if (this != &other) {
			_commands = std::move(other._commands);
		}
		return *this;
	}

	ActingState BehaviourComponent::Act(Registry& registry, WorldContext& worldContext, EntityId id)
	{
		// Execute commands in order until one succeeds or all fail.
		while (!_commands.empty()) {
			std::unique_ptr<BaseCommand>& command = _commands.front();
			if (command == nullptr) {
				_commands.pop_front();
				continue;
			}

			const BaseCommand::Status status = command->Execute(registry, worldContext, id);
			if (status == BaseCommand::Status::Success) {
				return ActingState::Actioning;
			}

			_commands.pop_front();
		}

		return ActingState::Inactive;
	}
} // namespace acid7beast::tbs
