// (c) 2025 Acid7Beast. Use with wisdom.
#include "HealthSystem.h"

#include <TBS/ECS/Registry/Registry.h>
#include <TBS/ECS/Components/Unit/Health/HealthComponent.h>
#include <TBS/System/WorldContext.h>
#include <algorithm>

namespace acid7beast::tbs
{
	void HealthSystem::Update(Registry& registry, WorldContext& worldContext)
	{
		// Health system update logic will be implemented here
		// This system will handle health-related processing
	}

	uint32_t HealthSystem::GetHealth(const HealthComponent& healthComponent)
	{
		uint32_t totalHealth = 0;
		for (const auto& durability : healthComponent.durabilities) {
			totalHealth += durability.durability;
		}
		return totalHealth;
	}

	DamageState HealthSystem::AcceptAttack(HealthComponent& healthComponent, int damage)
	{
		for (auto& durability : healthComponent.durabilities) {
			int compromise = std::min(damage, durability.durability);
			durability.durability -= compromise;
			damage -= compromise;
			if (damage <= 0) {
				break;
			}
		}

		if (GetHealth(healthComponent) <= 0) {
			return DamageState::Lethal;
		}

		return DamageState::Bearable;
	}

	void HealthSystem::AcceptHeal(HealthComponent& healthComponent, int heal)
	{
		for (auto& durability : healthComponent.durabilities) {
			int compromise = std::min(heal, durability.maxDurability - durability.durability);
			durability.durability += compromise;
			heal -= compromise;
			if (heal <= 0) {
				break;
			}
		}
	}

	bool HealthSystem::IsAlive(const HealthComponent& healthComponent)
	{
		return GetHealth(healthComponent) > 0;
	}
} // namespace acid7beast::tbs
