// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/ECS/Components/Unit/Common.h>
#include <TBS/ECS/Components/Unit/Behaviour/Commands/BaseCommand.h>
#include <TBS/ECS/Components/Unit/Behaviour/BehaviourComponent.h>
#include <memory>
#include <deque>

namespace acid7beast::tbs
{
	class Registry;
	struct WorldContext;

	enum class IsSimulationRunning : bool
	{
		No = false,
		Yes = true,
	};

	class BehaviourSystem final
	{
		// Public interface methods.
	public:
		IsSimulationRunning Update(Registry& registry, WorldContext& worldContext);
		
		// Static utility methods for behaviour operations
		static ActingState Act(BehaviourComponent& behaviourComponent, Registry& registry, WorldContext& worldContext, EntityId id);
		static void AddCommand(BehaviourComponent& behaviourComponent, std::unique_ptr<BaseCommand> command);
		static void ClearCommands(BehaviourComponent& behaviourComponent);
		static bool HasCommands(const BehaviourComponent& behaviourComponent);
	};
} // namespace acid7beast::tbs