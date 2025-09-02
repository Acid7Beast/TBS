// (c) 2025 Acid7Beast. Use with wisdom.

#include "Unit.h"

#include <TBS/World/WorldContext.h>

namespace acid7beast::tbs
{
	Unit::Unit(
		uint32_t unitId,
		std::unique_ptr<BaseBehaviourComponent> behaviourComponent,
		std::unique_ptr<BaseMovementComponent> movementComponent,
		std::unique_ptr<BaseHealthComponent> healthComponent,
		std::unique_ptr<BaseAttackComponent> attackComponent)
		: _unitId { unitId }
		, _behaviourComponent { std::move(behaviourComponent) }
		, _movementComponent { std::move(movementComponent) }
		, _healthComponent { std::move(healthComponent) }
		, _attackComponent { std::move(attackComponent) }
	{
		if (_behaviourComponent) {
			_behaviourComponent->SetOwner(*this);
		}

		if (_movementComponent) {
			_movementComponent->SetOwner(*this);
		}

		if (_healthComponent) {
			_healthComponent->SetOwner(*this);
		}
	}

	ActingState Unit::Act(WorldContext& worldContext)
	{
		if (!Health().IsAlive()) {
			return ActingState::Dead;
		}

		if (_behaviourComponent == nullptr) {
			return ActingState::Inactive;
		}

		return _behaviourComponent->Act(worldContext);
	}

	BaseBehaviourComponent& Unit::Behaviour()
	{
		if (_behaviourComponent == nullptr) {
			static EmptyBehaviourComponent empty {};
			return empty;
		}

		return *_behaviourComponent;
	}

	BaseMovementComponent& Unit::Movement()
	{
		if (_movementComponent == nullptr) {
			static EmptyMovementComponent empty { IVector2 { 0, 0 } };
			return empty;
		}

		return *_movementComponent;
	}

	BaseHealthComponent& Unit::Health()
	{
		if (_healthComponent == nullptr) {
			static EmptyHealthComponent empty {};
			return empty;
		}

		return *_healthComponent;
	}

	BaseAttackComponent& Unit::Attack()
	{
		if (_attackComponent == nullptr) {
			static EmptyAttackComponent empty {};
			return empty;
		}

		return *_attackComponent;
	}
} // namespace acid7beast::tbs
