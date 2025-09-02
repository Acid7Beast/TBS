// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "Components/Common.h"
#include "Components/Behaviour/BaseBehaviourComponent.h"
#include "Components/Movement/BaseMovementComponent.h"
#include "Components/Health/BaseHealthComponent.h"
#include "Components/Attack/BaseAttackComponent.h"

#include <TBS/Common.h>

#include <type_traits>

namespace acid7beast::tbs
{
	struct WorldContext;
	struct BehaviourVisitor;

	class Unit
	{
	public:
		Unit(uint32_t unitId,
			std::unique_ptr<BaseBehaviourComponent> behaviourComponent,
			std::unique_ptr<BaseMovementComponent> movementComponent,
			std::unique_ptr<BaseHealthComponent> healthComponent,
			std::unique_ptr<BaseAttackComponent> attackComponent);
		virtual ~Unit() = default;

	public:
		ActingState Act(WorldContext& worldContext);
		inline uint32_t GetId() const { return _unitId; }

		BaseBehaviourComponent& Behaviour();
		BaseMovementComponent& Movement();
		BaseHealthComponent& Health();
		BaseAttackComponent& Attack();

	private:
		uint32_t _unitId;
		std::unique_ptr<BaseBehaviourComponent> _behaviourComponent = nullptr;
		std::unique_ptr<BaseMovementComponent> _movementComponent = nullptr;
		std::unique_ptr<BaseHealthComponent> _healthComponent = nullptr;
		std::unique_ptr<BaseAttackComponent> _attackComponent = nullptr;
	};

} // namespace acid7beast::tbs
