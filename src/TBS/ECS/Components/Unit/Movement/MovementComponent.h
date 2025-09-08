// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Common.h>
#include <TBS/ECS/Components/Unit/Common.h>

namespace acid7beast::tbs
{
	struct WorldContext;

	class MovementComponent final
	{
		// Life-circle management.
	public:
		MovementComponent(const IVector2& position, int speed = 1, int groundDistance = 0);

		// Public interface methods.
	public:
		void RemoveFromWorld(WorldContext& worldContext, EntityId id);
		void MoveTo(WorldContext& worldContext, EntityId id, const IVector2& newPosition);
		const IVector2& GetPosition() const { return _position; }

		// Public properties.
	public:
		inline int GetGroundDistance() const { return _groundDistance; }
		inline int GetMovementSpeed() const { return _speed; }
		inline TravelMethod GetTravelMethod() const { return _groundDistance == 0 ? TravelMethod::Ground : TravelMethod::Air; }

		// Private state members.
	protected:
		IVector2 _position;
		int _speed = 0;
		int _groundDistance = 0;
	};
} // namespace acid7beast::tbs
