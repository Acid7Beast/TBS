// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Units/Components/Common.h>

namespace acid7beast::tbs
{
	class Unit;
	struct WorldContext;

	class BaseHealthComponent
	{
	public:
		virtual ~BaseHealthComponent() = default;

	public:
		inline void SetOwner(Unit& owner) { _owner = &owner; }
		DamageState AcceptAttack(WorldContext& worldContext, int damage, DamageReachability reachability);
		inline bool IsAlive() const { return GetHealth() > 0; }

	public:
		virtual uint32_t GetHealth() const = 0;

	protected:
		virtual DamageState TakeAndTestDamage(int damage) = 0;

	protected:
		Unit* _owner = nullptr;
	};

	class EmptyHealthComponent final : public BaseHealthComponent
	{
	public:
		inline uint32_t GetHealth() const override { return 0; }

	private:
		inline DamageState TakeAndTestDamage(int damage) override { return DamageState::Lethal; }
	};
} // namespace acid7beast::tbs
