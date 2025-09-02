// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Commands/CommandComposite.h>
#include <TBS/Commands/CommandFactory.h>
#include <TBS/Commands/DistantAttackCommand.h>
#include <TBS/Commands/MeleeAttackCommand.h>
#include <TBS/Commands/MoveCommand.h>
#include <TBS/Units/Components/Behaviour/HunterBehaviourComponent.h>
#include <TBS/Units/Components/Behaviour/SwordsmanBehaviourComponent.h>

#include <IO/Commands/March.hpp>

namespace acid7beast::tbs
{
	void CommandFactory<sw::io::March>::Visit(SwordsmanBehaviourComponent& behaviour)
	{
		std::unique_ptr<CommandComposite> command = std::make_unique<CommandComposite>();
		command->AddCommand(std::make_unique<MeleeAttackCommand>());
		command->AddCommand(
			std::make_unique<MoveCommand>(IVector2 { _params.targetX, _params.targetY }));

		behaviour.AddCommand(std::move(command));
	}

	void CommandFactory<sw::io::March>::Visit(HunterBehaviourComponent& behaviour)
	{
		std::unique_ptr<CommandComposite> command = std::make_unique<CommandComposite>();
		command->AddCommand(std::make_unique<MeleeAttackCommand>());
		command->AddCommand(std::make_unique<DistantAttackCommand>());
		command->AddCommand(
			std::make_unique<MoveCommand>(IVector2 { _params.targetX, _params.targetY }));

		behaviour.AddCommand(std::move(command));
	}
} // namespace acid7beast::tbs
