// (c) 2025 Acid7Beast. Use with wisdom.
#include "MovementSystem.h"

#include <TBS/ECS/Registry/Registry.h>
#include <TBS/ECS/Components/Unit/Movement/MovementComponent.h>
#include <TBS/System/WorldContext.h>

namespace acid7beast::tbs
{
	void MovementSystem::Update(Registry& registry, WorldContext& worldContext)
	{
		// Movement system update logic will be implemented here
		// This system will handle movement processing
	}

	void MovementSystem::RemoveFromWorld(Registry& registry, WorldContext& worldContext, EntityId id)
	{
		if (auto* movement = registry.GetComponent<MovementComponent>(id)) {
			worldContext.map.RemoveEntity(id, movement->position);
		}
	}

	void MovementSystem::MoveTo(Registry& registry, WorldContext& worldContext, EntityId id, const IVector2& newPosition)
	{
		if (auto* movement = registry.GetComponent<MovementComponent>(id)) {
			worldContext.map.RemoveEntity(id, movement->position);
			movement->position = newPosition;
			worldContext.map.PlaceEntity(id, movement->position);
		}
	}

	TravelMethod MovementSystem::GetTravelMethod(const MovementComponent& movementComponent)
	{
		return movementComponent.groundDistance == 0 ? TravelMethod::Ground : TravelMethod::Air;
	}
} // namespace acid7beast::tbs
