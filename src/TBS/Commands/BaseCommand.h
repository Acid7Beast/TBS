// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

namespace acid7beast::tbs
{
	struct WorldContext;
	class Unit;

	class BaseCommand
	{
	public:
		enum class Status : bool
		{
			Fail = false,
			Success = true,
		};

		virtual ~BaseCommand() = default;

	public:
		virtual void Pend(WorldContext& worldContext, Unit& unit) {}
		virtual Status Execute(WorldContext& worldContext, Unit& unit) = 0;
	};
} // namespace acid7beast::tbs
