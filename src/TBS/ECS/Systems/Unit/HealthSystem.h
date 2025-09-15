// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/ECS/Components/Unit/Common.h>
#include <TBS/ECS/Components/Unit/Health/HealthComponent.h>

namespace acid7beast::tbs
{
	class Registry;
	struct WorldContext;

	class HealthSystem final
	{
		// Public interface methods.
	public:
		void Update(Registry& registry, WorldContext& worldContext);
		
		// Static utility methods for health operations
		static uint32_t GetHealth(const HealthComponent& healthComponent);
		static DamageState AcceptAttack(HealthComponent& healthComponent, int damage);
		static void AcceptHeal(HealthComponent& healthComponent, int heal);
		static bool IsAlive(const HealthComponent& healthComponent);
	};
} // namespace acid7beast::tbs
