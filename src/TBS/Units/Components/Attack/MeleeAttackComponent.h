// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseAttackComponent.h"

namespace acid7beast::tbs
{
	class MeleeAttackComponent final : public BaseAttackComponent
	{
	public:
		MeleeAttackComponent(int meleeDamage);

	public:
		uint32_t GetAttackDamage(DamageReachability reachability) const override;
		inline uint32_t GetAttackDistance() const { return 1; }

	private:
		int _meleeDamage;
	};
} // namespace acid7beast::tbs
