// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Common.h>

namespace acid7beast::tbs
{
	class Registry;
	struct WorldContext;

	class BaseCommand
	{
		// Public nested types.
	public:
		enum class Status : bool
		{
			Fail = false,
			Success = true,
		};

		// Life-circle management.
	public:
		virtual ~BaseCommand() = default;

		// Public interface methods.
	public:
		virtual void Pend(Registry& registry, WorldContext& worldContext, EntityId id) {}
		virtual Status Execute(Registry& registry, WorldContext& worldContext, EntityId id) = 0;
	};
} // namespace acid7beast::tbs
