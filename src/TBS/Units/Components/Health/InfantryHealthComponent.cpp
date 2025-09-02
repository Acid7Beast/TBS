// (c) 2025 Acid7Beast. Use with wisdom.

#include "InfantryHealthComponent.h"

namespace acid7beast::tbs
{
	InfantryHealthComponent::InfantryHealthComponent(int health)
		: BaseHealthComponent::BaseHealthComponent {}
		, _health { health }
	{
	}

	DamageState InfantryHealthComponent::TakeAndTestDamage(int damage)
	{
		_health -= damage;
		if (_health <= 0) {
			_health = 0;
			return DamageState::Lethal;
		}

		return DamageState::Bearable;
	}
} // namespace acid7beast::tbs
