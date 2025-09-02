// (c) 2025 Acid7Beast. Use with wisdom.

#include "Simulation.h"

#include <TBS/Commands/CommandFactory.h>
#include <TBS/Units/UnitFactory.h>
#include <TBS/System/EventLogger.h>

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

	void Simulation::SpawnUnit(BaseUnitFactory&& factory)
	{
		factory.SpawnUnit(_worldContext);
	}

	void Simulation::EnqueueCommand(uint32_t unitId, BehaviourVisitor&& factory)
	{
		auto unitIter = _worldContext.units.find(unitId);
		if (unitIter == _worldContext.units.end()) {
			return;
		}

		Unit* unit = unitIter->second.get();
		if (unit) {
			unit->Behaviour().Visit(factory);
		}
	}

	void Simulation::Run()
	{
		while (Tick() == true)
			;
	}

	bool Simulation::Tick()
	{
		uint64_t activeUnits = 0;

		++_worldContext.tick;
		std::erase_if(
			_worldContext.units,
			[&worldContext = _worldContext, &activeUnits](auto& pair) {
				auto& unit = pair.second;
				if (!unit) {
					return true;
				}

				ActingState status = unit->Act(worldContext);
				if (status == ActingState::Dead) {
					return true;
				}

				if (status == ActingState::Actioning) {
					++activeUnits;
				}

				return false;
			});

		// Continue simulation untill has units and at least one unid can act.
		return activeUnits > 0 && _worldContext.units.size() > 1;
	}
} // namespace acid7beast::tbs
