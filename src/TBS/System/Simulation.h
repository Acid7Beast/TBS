// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "../Common.h"

#include <TBS/ECS/Registry/Registry.h>
#include <TBS/ECS/Systems/Unit/BehaviourSystem.h>
#include <TBS/ECS/Systems/Unit/CleanupSystem.h>
#include <TBS/System/EventLogger.h>
#include <TBS/System/WorldContext.h>

namespace acid7beast::tbs
{
	class BaseCommandFactory;
	class BaseEntityFactory;
	class BaseUnitFactory;

	class Simulation final
	{
		// Life-circle management.
	public:
		Simulation(BaseEventLogger& logger);

		// Public interface methods.
	public:
		void CreateWorld(const IVector2& size);
		void SpawnEntity(BaseEntityFactory&& factory);
		void EnqueueCommand(EntityId id, BaseCommandFactory&& factory);
		void Run();

		// Private interface methods.
	private:
		IsSimulationRunning Tick();

		// Private state members.
	private:
		Registry _registry;
		WorldContext _worldContext;
		BehaviourSystem _behaviourSystem;
		CleanupSystem _cleanUpSystem;
	};
} // namespace acid7beast::tbs
