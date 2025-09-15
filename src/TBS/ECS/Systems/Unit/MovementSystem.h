// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Common.h>
#include <TBS/ECS/Components/Unit/Common.h>
#include <TBS/ECS/Components/Unit/Movement/MovementComponent.h>

namespace acid7beast::tbs
{
	class Registry;
	struct WorldContext;

	class MovementSystem final
	{
		// Public interface methods.
	public:
		void Update(Registry& registry, WorldContext& worldContext);
		
		// Static utility methods for movement operations
		static void RemoveFromWorld(Registry& registry, WorldContext& worldContext, EntityId id);
		static void MoveTo(Registry& registry, WorldContext& worldContext, EntityId id, const IVector2& newPosition);
		static TravelMethod GetTravelMethod(const MovementComponent& movementComponent);
	};
} // namespace acid7beast::tbs
