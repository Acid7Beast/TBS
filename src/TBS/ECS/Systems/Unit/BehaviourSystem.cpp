// (c) 2025 Acid7Beast. Use with wisdom.
#include "BehaviourSystem.h"

#include <TBS/ECS/Registry/Registry.h>
#include <TBS/ECS/Events/EventBus.h>
#include <TBS/ECS/Components/Unit/Behaviour/BehaviourComponent.h>
#include <TBS/ECS/Components/Unit/Health/HealthComponent.h>
#include <TBS/System/WorldContext.h>
#include <algorithm>
#include <vector>

namespace acid7beast::tbs
{
	IsSimulationRunning BehaviorsSystem::Update(Registry& registry, WorldContext& worldContext)
	{
		uint32_t activeUnits = 0;

		auto& behaviourStorage = registry.GetStorage<BehaviourComponent>();

		for (EntityId entityId : worldContext.turnOrder) {
			if (auto* health = registry.GetComponent<HealthComponent>(entityId)) {
				if (health->GetHealth() <= 0) {
					continue;
				}
			}

			BehaviourComponent* behaviour = behaviourStorage.GetComponent(entityId);
			if (behaviour == nullptr) {
				continue;
			}

			if (behaviour->Act(registry, worldContext, entityId) == ActingState::Actioning) {
				++activeUnits;
			}
		}

		const bool isSimulationRunning = (activeUnits > 0 && behaviourStorage.Size() > 1);
		return static_cast<IsSimulationRunning>(isSimulationRunning);
	}
} // namespace acid7beast::tbs
