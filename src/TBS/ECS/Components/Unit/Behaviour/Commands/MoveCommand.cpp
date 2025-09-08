// (c) 2025 Acid7Beast. Use with wisdom.

#include "MoveCommand.h"

#include <TBS/System/WorldContext.h>
#include <TBS/ECS/Registry/Registry.h>
#include <TBS/ECS/Components/Unit/Movement/MovementComponent.h>

namespace acid7beast::tbs
{
	namespace MoveCommandInternal
	{
		IVector2 GetPositionInDirection(const IVector2& currentPosition, const IVector2& targetPosition, int speed)
		{
			const IVector2 delta { targetPosition - currentPosition };

			const int stepX = (delta.x > 0) ? 1 : ((delta.x < 0) ? -1 : 0);
			const int stepY = (delta.y > 0) ? 1 : ((delta.y < 0) ? -1 : 0);

			return { currentPosition.x + stepX * speed, currentPosition.y + stepY * speed };
		}
	}

	MoveCommand::MoveCommand(const IVector2& targetPosition)
		: _targetPosition { targetPosition }
	{}

	void MoveCommand::Pend(Registry& registry, WorldContext& worldContext, EntityId id)
	{
		auto* movementComponent = registry.GetComponent<MovementComponent>(id);
		if (movementComponent == nullptr) {
			return;
		}

		worldContext.logger.LogMarchStarted(worldContext.tick, id, movementComponent->GetPosition(), _targetPosition);
	}

	BaseCommand::Status MoveCommand::Execute(Registry& registry, WorldContext& worldContext, EntityId id)
	{
		using namespace MoveCommandInternal;

		auto* movementComponent = registry.GetComponent<MovementComponent>(id);
		if (movementComponent == nullptr) {
			return Status::Fail;
		}
		
		const IVector2& currentPosition = movementComponent->GetPosition();
		if (currentPosition == _targetPosition) {
			return Status::Fail;
		}

		const IVector2 newPosition = GetPositionInDirection(currentPosition, _targetPosition, movementComponent->GetMovementSpeed());
		const bool isAirUnit = (movementComponent->GetTravelMethod() == TravelMethod::Air);
		const bool canMove = (isAirUnit || !worldContext.map.IsCellOccupied(newPosition));
		if (!canMove) {
			return Status::Fail;
		}

		movementComponent->MoveTo(worldContext, id, newPosition);
		worldContext.logger.LogEntityMoved(worldContext.tick, id, newPosition);

		if (newPosition == _targetPosition) {
			worldContext.logger.LogMarchEnded(worldContext.tick, id, _targetPosition);
		}

		return Status::Success;
	}
} // namespace acid7beast::tbs
