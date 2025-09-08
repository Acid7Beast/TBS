// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

namespace acid7beast::tbs
{
	class Registry;
	class WorldContext;

	enum class IsSimulationRunning : bool
	{
		No = false,
		Yes = true,
	};

	class BehaviorsSystem final
	{
		// Public interface methods.
	public:
		IsSimulationRunning Update(Registry& registry, WorldContext& worldContext);
	};
} // namespace acid7beast::tbs