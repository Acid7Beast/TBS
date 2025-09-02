// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Units/Components/Common.h>

namespace acid7beast::tbs
{
	class BaseAttackComponent
	{
	public:
		virtual ~BaseAttackComponent() = default;

	public:
		virtual uint32_t GetAttackDamage(DamageReachability reachability) const = 0;
		virtual uint32_t GetAttackDistance() const = 0;
	};

	class EmptyAttackComponent final : public BaseAttackComponent
	{
	public:
		inline uint32_t GetAttackDamage(DamageReachability /*reachability*/) const override { return 0; }
		inline uint32_t GetAttackDistance() const override { return 0; }
	};
} // namespace acid7beast::tbs
