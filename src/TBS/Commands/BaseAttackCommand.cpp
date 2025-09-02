// (c) 2025 Acid7Beast. Use with wisdom.

#include "BaseAttackCommand.h"

#include <TBS/World/WorldContext.h>
#include <random>

namespace acid7beast::tbs
{
	namespace BaseAttackCommandInternal
	{
		size_t GetRandomIndex(size_t count)
		{
			static std::random_device rd;
			static std::mt19937 gen(rd());

			std::uniform_int_distribution<size_t> distrib(0, count - 1);

			return distrib(gen);
		}
	}

	BaseAttackCommand::BaseAttackCommand(DamageReachability reachability)
		: _reachability { reachability }
	{}

	BaseCommand::Status BaseAttackCommand::Execute(WorldContext& worldContext, Unit& unit)
	{
		using namespace BaseAttackCommandInternal;

		const uint32_t damage = unit.Attack().GetAttackDamage(_reachability);
		if (damage == 0) {
			return Status::Fail;
		}

		std::vector<Unit*> enemies = GetEnemies(worldContext, unit);
		if (enemies.empty()) {
			return Status::Fail;
		}

		Unit* enemy = enemies.at(GetRandomIndex(enemies.size()));
		if (enemy == nullptr) {
			return Status::Fail;
		}

		DamageState damageState = enemy->Health().AcceptAttack(worldContext, damage, _reachability);

		worldContext.logger.LogUnitAttacked(
			worldContext.tick, unit.GetId(), enemy->GetId(), damage, enemy->Health().GetHealth());

		if (damageState == DamageState::Lethal) {
			worldContext.logger.LogUnitDied(worldContext.tick, enemy->GetId());
		}

		return Status::Success;
	}
} // namespace acid7beast::tbs
