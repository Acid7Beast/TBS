// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/ECS/Components/Unit/Common.h>

#include <vector>

namespace acid7beast::tbs
{
	struct Weapon
	{
		int startRange;
		int endRange;
		int damage;
		DamageReachability reachability;
	};

	class AttackComponent final
	{
		// Life-cycle management.
	public:
		AttackComponent(std::vector<Weapon> weapons);

		// Public interface methods.
	public:
		inline const std::vector<Weapon>& GetWeapons() const { return _weapons; }

		// Private state members.
	private:
		std::vector<Weapon> _weapons;
	};
} // namespace acid7beast::tbs
