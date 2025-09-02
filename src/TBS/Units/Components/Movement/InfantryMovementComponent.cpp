// (c) 2025 Acid7Beast. Use with wisdom.

#include "InfantryMovementComponent.h"

namespace acid7beast::tbs
{
	InfantryMovementComponent::InfantryMovementComponent(const IVector2& position, int speed)
		: BaseMovementComponent { position }
		, _speed { speed }
	{
	}
} // namespace acid7beast::tbs
