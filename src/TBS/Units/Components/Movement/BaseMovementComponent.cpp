// (c) 2025 Acid7Beast. Use with wisdom.

#include "BaseMovementComponent.h"

#include <TBS/World/WorldContext.h>
#include <TBS/Units/Unit.h>

namespace acid7beast::tbs
{
	BaseMovementComponent::BaseMovementComponent(const IVector2& position)
		: _position { position }
	{
	}

	void BaseMovementComponent::RemoveFromWorld(WorldContext& worldContext)
	{
		if (_owner == nullptr)
		{
			return;
		}

		worldContext.map.RemoveUnit(_owner->GetId(), _position);
	}

	void BaseMovementComponent::MoveTo(WorldContext& worldContext, const IVector2& newPosition)
	{
		if (_owner == nullptr)
		{
			return;
		}

		worldContext.map.RemoveUnit(_owner->GetId(), _position);
		_position = newPosition;
		worldContext.map.PlaceUnit(_owner->GetId(), _position);
	}
	
	EmptyMovementComponent::EmptyMovementComponent(const IVector2& position)
		: BaseMovementComponent { position }
	{
	}
} // namespace acid7beast::tbs
