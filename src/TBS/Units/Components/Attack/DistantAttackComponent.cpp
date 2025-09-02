// (c) 2025 Acid7Beast. Use with wisdom.

#include "DistantAttackComponent.h"

namespace acid7beast::tbs
{
	DistantAttackComponent::DistantAttackComponent(int range, int meleeDamage, int distantDamage)
		: _range { range }
		, _meleeDamage { meleeDamage }
		, _distantDamage { distantDamage }
	{}

	uint32_t DistantAttackComponent::GetAttackDamage(DamageReachability reachability) const
	{
		switch (reachability) {
			case DamageReachability::Melee:
				return _meleeDamage;
			case DamageReachability::Distant:
				return _distantDamage;
			default:
				break;
		}

		return 0;
	}
} // namespace acid7beast::tbs
