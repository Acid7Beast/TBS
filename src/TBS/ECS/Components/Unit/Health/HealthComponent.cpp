// (c) 2025 Acid7Beast. Use with wisdom.

#include "HealthComponent.h"

#include <TBS/System/WorldContext.h>
#include <TBS/ECS/Components/Unit/Common.h>

namespace acid7beast::tbs
{
	HealthComponent::HealthComponent(std::vector<Durability> durabilities)
		: _durabilities { durabilities }
	{
	}

	uint32_t HealthComponent::GetHealth() const
	{
		uint32_t totalHealth = 0;
		for (const auto& durability : _durabilities) {
			totalHealth += durability.durability;
		}
		return totalHealth;
	}

	DamageState HealthComponent::AcceptAttack(int damage)
	{
		for (auto& durability : _durabilities) {
			int compromise = std::min(damage, durability.durability);
			durability.durability -= compromise;
			damage -= compromise;
			if (damage <= 0) {
				break;
			}
		}

		if (GetHealth() <= 0) {
			return DamageState::Lethal;
		}

		return DamageState::Bearable;
	}

	void HealthComponent::AcceptHeal(int heal)
	{
		for (auto& durability : _durabilities) {
			int compromise = std::min(heal, durability.maxDurability - durability.durability);
			durability.durability += compromise;
			heal -= compromise;
			if (heal <= 0) {
				break;
			}
		}
	}
} // namespace acid7beast::tbs
