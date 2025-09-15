// (c) 2025 Acid7Beast. Use with wisdom.

#include "AttackCommand.h"

#include <TBS/ECS/Registry/Registry.h>
#include <TBS/System/WorldContext.h>
#include <TBS/ECS/Components/Unit/Attack/AttackComponent.h>
#include <TBS/ECS/Components/Unit/Health/HealthComponent.h>
#include <TBS/ECS/Components/Unit/Movement/MovementComponent.h>
#include <TBS/ECS/Components/Unit/Common.h>
#include <TBS/ECS/Events/Unit/DeathEvent.h>
#include <TBS/ECS/Systems/Unit/HealthSystem.h>

#include <random>

namespace acid7beast::tbs
{
	namespace AttackCommandInternal
	{
		size_t GetRandomIndex(size_t count)
		{
			static std::random_device rd;
			static std::mt19937 gen(rd());

			std::uniform_int_distribution<size_t> distrib(0, count - 1);

			return distrib(gen);
		}

		std::vector<EntityId> GetEnemies(Registry& registry, WorldContext& worldContext, EntityId id, const Weapon& weapon)
		{
			MovementComponent* movementComponent = registry.GetComponent<MovementComponent>(id);
			if (movementComponent == nullptr)
			{
				return {};
			}

			return worldContext.map.GetEntitiesInRadius(
				registry,
				movementComponent->position,
				id,
				weapon.startRange,
				weapon.endRange + 1,
				weapon.reachability);
		}
	}

	BaseCommand::Status AttackCommand::Execute(Registry& registry, WorldContext& worldContext, EntityId id)
	{
		using namespace AttackCommandInternal;

		auto* attackComponent = registry.GetComponent<AttackComponent>(id);
		if (attackComponent == nullptr) {
			return Status::Fail;
		}
		for (const auto& weapon : attackComponent->weapons) {
			const uint32_t damage = weapon.damage;
			if (damage == 0) {
				continue;
			}

			std::vector<EntityId> enemies = GetEnemies(registry, worldContext, id, weapon);
			if (enemies.empty()) {
				continue;
			}

			EntityId enemyId = enemies.at(GetRandomIndex(enemies.size()));
			auto* enemyComponent = registry.GetComponent<HealthComponent>(enemyId);
			if (enemyComponent == nullptr) {
				continue;
			}

			DamageState damageState = HealthSystem::AcceptAttack(*enemyComponent, damage);

			worldContext.logger.LogEntityAttacked(
				worldContext.tick, id, enemyId, damage, HealthSystem::GetHealth(*enemyComponent));

			if (damageState == DamageState::Lethal) {
				MovementComponent* enemyMovementComponent = registry.GetComponent<MovementComponent>(enemyId);
				worldContext.eventBus.PushEvent(DeathEvent { enemyId });
				worldContext.logger.LogEntityDied(worldContext.tick, enemyId);
			}

			return Status::Success;
		}

		return Status::Fail;
	}
} // namespace acid7beast::tbs
