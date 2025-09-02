// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/World/WorldContext.h>

namespace acid7beast::tbs
{
	class BaseUnitFactory;

	class Simulation final
	{
	public:
		Simulation(BaseEventLogger& logger);

	public:
		void CreateWorld(const IVector2& size);
		void SpawnUnit(BaseUnitFactory&& factory);
		void EnqueueCommand(uint32_t unitId, BehaviourVisitor&& factory);
		void Run();

	private:
		bool Tick();

	private:
		WorldContext _worldContext;
	};
} // namespace acid7beast::tbs
