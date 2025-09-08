// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/System/CommandFactory.h>

#include <TBS/ECS/Components/Unit/Behaviour/Commands/CommandComposite.h>
#include <TBS/ECS/Components/Unit/Behaviour/Commands/AttackCommand.h>
#include <TBS/ECS/Components/Unit/Behaviour/Commands/MoveCommand.h>

#include <IO/Commands/March.hpp>

namespace acid7beast::tbs
{
	void CommandFactory<sw::io::March>::SpawnCommand(Registry& registry, WorldContext& worldContext, EntityId id)
	{
		BehaviourComponent* behaviourComponent = registry.GetComponent<BehaviourComponent>(id);
		if (behaviourComponent == nullptr) {
			return;
		}

		std::unique_ptr<CommandComposite> command = std::make_unique<CommandComposite>();
		command->AddCommand(std::make_unique<AttackCommand>());
		command->AddCommand(
			std::make_unique<MoveCommand>(IVector2 { _params.targetX, _params.targetY }));

		behaviourComponent->AddCommand(std::move(command));
	}

} // namespace acid7beast::tbs
