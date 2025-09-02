// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseHealthComponent.h"

namespace acid7beast::tbs
{
	class InfantryHealthComponent final : public BaseHealthComponent
	{
	public:
		InfantryHealthComponent(int health);

	public:
		inline uint32_t GetHealth() const override { return _health; }

	private:
		DamageState TakeAndTestDamage(int damage) override;

	private:
		int _health;
	};
} // namespace acid7beast::tbs
