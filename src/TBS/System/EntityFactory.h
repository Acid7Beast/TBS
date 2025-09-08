// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <memory>

namespace acid7beast::tbs
{
	class Registry;
	struct WorldContext;

	class BaseEntityFactory
	{
		// Public virtual interface methods.
	public:
		virtual void SpawnEntity(Registry& registry, WorldContext& worldContext) = 0;
	};

	template<typename SpawnParams>
	class EntityFactory final : public BaseEntityFactory
	{
		// Life-circle management.
	public:
		inline EntityFactory(SpawnParams&& params)
			: _params(std::move(params))
		{}

		// Public inherited interface methods.
	public:
		inline void SpawnEntity(Registry& registry, WorldContext& worldContext) override;

		// Private state members.
	private:
		SpawnParams _params;
	};
} // namespace acid7beast::tbs
