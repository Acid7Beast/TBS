// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseMovementComponent.h"

namespace acid7beast::tbs
{
	class InfantryMovementComponent final : public BaseMovementComponent
	{
	public:
		InfantryMovementComponent(const IVector2& position, int speed = 1);

	private:
		inline int GetGroundDistance() const { return 0; }
		inline int GetMovementSpeed() const { return _speed; }
		inline MovementType GetMovementType() const override { return MovementType::Ground; }
		inline MovementState GetMovementState() const override { return MovementState::Movable; };

	private:
		int _speed;
	};
} // namespace acid7beast::tbs
