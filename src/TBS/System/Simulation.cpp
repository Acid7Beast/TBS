// (c) 2025 Acid7Beast. Use with wisdom.

#include "Simulation.h"

#include <TBS/System/CommandFactory.h>
#include <TBS/System/EntityFactory.h>
#include <TBS/System/EventLogger.h>
#include <TBS/ECS/Components/Unit/Behaviour/BehaviourComponent.h>

#include <numeric>

namespace acid7beast::tbs
{
	Simulation::Simulation(BaseEventLogger& logger)
		: _worldContext { logger }
	{}

	void Simulation::CreateWorld(const IVector2& size)
	{
		_worldContext.map.Create(size);
		_worldContext.logger.LogMapCreated(_worldContext.tick, size);
	}

	void Simulation::SpawnEntity(BaseEntityFactory&& factory)
	{
		factory.SpawnEntity(_registry, _worldContext);
	}

	void Simulation::EnqueueCommand(EntityId id, BaseCommandFactory&& factory)
	{ 
		factory.SpawnCommand(_registry, _worldContext, id);
	}

	void Simulation::Run()
	{
		while (true)
		{
			if (Tick() == IsSimulationRunning::No) {
				break;
			}
		}
	}

	IsSimulationRunning Simulation::Tick()
	{
		++_worldContext.tick;

		const IsSimulationRunning preCleanupRunning = _behaviorsSystem.Update(_registry, _worldContext);

		_cleanUpSystem.Update(_registry, _worldContext);

		const auto& behaviourStorage = _registry.GetStorage<BehaviourComponent>();
		const bool hasMultipleUnits = (behaviourStorage.Size() > 1);
		const bool isSimulationRunning = (preCleanupRunning == IsSimulationRunning::Yes) && hasMultipleUnits;
		return static_cast<IsSimulationRunning>(isSimulationRunning);
	}
} // namespace acid7beast::tbs
