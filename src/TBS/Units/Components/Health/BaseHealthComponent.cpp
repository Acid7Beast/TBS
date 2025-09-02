// (c) 2025 Acid7Beast. Use with wisdom.

#include "BaseHealthComponent.h"

#include <TBS/World/WorldContext.h>

namespace acid7beast::tbs
{
	DamageState BaseHealthComponent::AcceptAttack(WorldContext& worldContext, int damage, DamageReachability reachability)
	{
		if (_owner == nullptr)
		{
			return DamageState::Lethal;
		}

		// Deal damage from attacker to this unit.
		const DamageState damageState = TakeAndTestDamage(damage);

		// Check if this unit is dead.
		if (damageState == DamageState::Lethal) {
			_owner->Movement().RemoveFromWorld(worldContext);
			_owner->Behaviour().AddCommand(nullptr);
		}

		return damageState;
	}
} // namespace acid7beast::tbs
