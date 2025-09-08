// (c) 2025 Acid7Beast. Use with wisdom.

#include "MovementComponent.h"

#include <TBS/System/WorldContext.h>

namespace acid7beast::tbs
{
	MovementComponent::MovementComponent(const IVector2& position, int speed, int groundDistance)
		: _position { position }
		, _speed { speed }
		, _groundDistance { groundDistance }
	{
	}

	void MovementComponent::RemoveFromWorld(WorldContext& worldContext, EntityId id)
	{
		worldContext.map.RemoveEntity(id, _position);
	}

	void MovementComponent::MoveTo(WorldContext& worldContext, EntityId id, const IVector2& newPosition)
	{
		worldContext.map.RemoveEntity(id, _position);
		_position = newPosition;
		worldContext.map.PlaceEntity(id, _position);
	}
} // namespace acid7beast::tbs
