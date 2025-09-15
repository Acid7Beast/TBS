// (c) 2025 Acid7Beast. Use with wisdom.
#include "BehaviourSystem.h"

#include <TBS/ECS/Registry/Registry.h>
#include <TBS/ECS/Events/EventBus.h>
#include <TBS/ECS/Components/Unit/Behaviour/BehaviourComponent.h>
#include <TBS/ECS/Components/Unit/Health/HealthComponent.h>
#include <TBS/System/WorldContext.h>
#include <TBS/ECS/Systems/Unit/HealthSystem.h>
#include <algorithm>
#include <vector>

namespace acid7beast::tbs
{
	IsSimulationRunning BehaviourSystem::Update(Registry& registry, WorldContext& worldContext)
	{
		uint32_t activeUnits = 0;

		auto& behaviourStorage = registry.GetStorage<BehaviourComponent>();

		for (EntityId entityId : worldContext.turnOrder) {
			if (auto* health = registry.GetComponent<HealthComponent>(entityId)) {
				if (HealthSystem::GetHealth(*health) <= 0) {
					continue;
				}
			}

			BehaviourComponent* behaviour = behaviourStorage.GetComponent(entityId);
			if (behaviour == nullptr) {
				continue;
			}

			if (Act(*behaviour, registry, worldContext, entityId) == ActingState::Actioning) {
				++activeUnits;
			}
		}

		const bool isSimulationRunning = (activeUnits > 0 && behaviourStorage.Size() > 1);
		return static_cast<IsSimulationRunning>(isSimulationRunning);
	}

	ActingState BehaviourSystem::Act(BehaviourComponent& behaviourComponent, Registry& registry, WorldContext& worldContext, EntityId id)
	{
		// Execute commands in order until one succeeds or all fail.
		while (!behaviourComponent.commands.empty()) {
			std::unique_ptr<BaseCommand>& command = behaviourComponent.commands.front();
			if (command == nullptr) {
				behaviourComponent.commands.pop_front();
				continue;
			}

			const BaseCommand::Status status = command->Execute(registry, worldContext, id);
			if (status == BaseCommand::Status::Success) {
				return ActingState::Actioning;
			}

			behaviourComponent.commands.pop_front();
		}

		return ActingState::Inactive;
	}

	void BehaviourSystem::AddCommand(BehaviourComponent& behaviourComponent, std::unique_ptr<BaseCommand> command)
	{
		behaviourComponent.commands.push_back(std::move(command));
	}

	void BehaviourSystem::ClearCommands(BehaviourComponent& behaviourComponent)
	{
		behaviourComponent.commands.clear();
	}

	bool BehaviourSystem::HasCommands(const BehaviourComponent& behaviourComponent)
	{
		return !behaviourComponent.commands.empty();
	}
} // namespace acid7beast::tbs
