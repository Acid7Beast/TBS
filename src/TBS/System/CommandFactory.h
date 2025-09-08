// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "../Common.h"

namespace acid7beast::tbs
{
	class Registry;
	class WorldContext;

	class BaseCommandFactory
	{
		// Life-circle management.
	public:
		virtual ~BaseCommandFactory() = default;

		// Public interface methods.
	public:
		virtual void SpawnCommand(Registry& registry, WorldContext& worldContext, EntityId id) = 0;
	};

	template <typename CommandParams>
	class CommandFactory final : public BaseCommandFactory
	{
		// Life-circle management.
	public:
		CommandFactory(CommandParams&& params)
			: _params(std::move(params))
		{}

		// Public interface methods.
	public:
		inline void SpawnCommand(Registry& registry, WorldContext& worldContext, EntityId id) override;

		// Private state members.
	private:
		CommandParams _params;
	};
}  // namespace acid7beast::tbs
