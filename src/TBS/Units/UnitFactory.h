// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <memory>

namespace acid7beast::tbs
{
	class Unit;
	struct WorldContext;

	class BaseUnitFactory
	{
	public:
		virtual void SpawnUnit(WorldContext& worldContext) = 0;
	};

	template <typename SpawnParams>
	class UnitFactory : public BaseUnitFactory
	{
	public:
		UnitFactory(SpawnParams&& params) :
				_params(std::move(params))
		{}

		inline void SpawnUnit(WorldContext& worldContext) override;

	private:
		SpawnParams _params;
	};
}  // namespace acid7beast::tbs
