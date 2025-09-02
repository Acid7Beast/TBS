// (c) 2025 Acid7Beast. Use with wisdom.

#include "MeleeAttackComponent.h"

namespace acid7beast::tbs
{
	MeleeAttackComponent::MeleeAttackComponent(int meleeDamage)
		: _meleeDamage { meleeDamage }
	{}

	uint32_t MeleeAttackComponent::GetAttackDamage(DamageReachability reachability) const
	{
		switch (reachability) {
			case DamageReachability::Melee:
				return _meleeDamage;
			case DamageReachability::Distant:
			default:
				break;
		}

		return 0;
	}
} // namespace acid7beast::tbs
