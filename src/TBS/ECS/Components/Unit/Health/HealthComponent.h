// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/ECS/Components/Unit/Common.h>
#include <vector>

namespace acid7beast::tbs
{
	struct Durability
	{
		int durability;
		int maxDurability;
	};
	
	class HealthComponent final
	{
		// Life-cycle management.
	public:
		HealthComponent(std::vector<Durability> durabilities);

		// Public interface methods.
	public:
		DamageState AcceptAttack(int damage);
		void AcceptHeal(int heal);
		inline bool IsAlive() const { return GetHealth() > 0; }
		uint32_t GetHealth() const;

		// Private state members.
	private:
		std::vector<Durability> _durabilities;
	};
} // namespace acid7beast::tbs
