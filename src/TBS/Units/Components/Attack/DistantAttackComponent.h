// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseAttackComponent.h"

namespace acid7beast::tbs
{
	class DistantAttackComponent final : public BaseAttackComponent
	{
	public:
		DistantAttackComponent(int range, int meleeDamage, int distantDamage);

	public:
		uint32_t GetAttackDamage(DamageReachability reachability) const override;
		inline uint32_t GetAttackDistance() const { return _range; }

	private:
		int _meleeDamage;
		int _distantDamage;
		int _range;
	};
} // namespace acid7beast::tbs
