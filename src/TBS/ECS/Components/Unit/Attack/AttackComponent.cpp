// (c) 2025 Acid7Beast. Use with wisdom.

#include "AttackComponent.h"

namespace acid7beast::tbs
{
	AttackComponent::AttackComponent(std::vector<Weapon> weapons)
		: _weapons { std::move(weapons) }
	{}
} // namespace acid7beast::tbs
