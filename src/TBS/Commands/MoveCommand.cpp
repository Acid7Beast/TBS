// (c) 2025 Acid7Beast. Use with wisdom.

#include "MoveCommand.h"

#include <TBS/World/WorldContext.h>

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

	void MoveCommand::Pend(WorldContext& worldContext, Unit& unit)
	{
		worldContext.logger.LogMarchStarted(worldContext.tick, unit.GetId(), unit.Movement().GetPosition(), _targetPosition);
	}

	BaseCommand::Status MoveCommand::Execute(WorldContext& worldContext, Unit& unit)
	{
		using namespace MoveCommandInternal;

		// Filter non-movable units.
		if (unit.Movement().GetMovementState() == MovementState::Building) {
			return Status::Fail;
		}

		const IVector2& currentPosition = unit.Movement().GetPosition();
		if (currentPosition == _targetPosition) {
			return Status::Fail;
		}

		// Check possibility to move.
		const IVector2 newPosition = GetPositionInDirection(currentPosition, _targetPosition, unit.Movement().GetMovementSpeed());
		const bool isAirUnit = (unit.Movement().GetMovementType() == MovementType::Air);
		const bool canMove = (isAirUnit || !worldContext.map.IsCellOccupied(newPosition));
		if (!canMove) {
			return Status::Fail;
		}

		// Do unit movement.
		unit.Movement().MoveTo(worldContext, newPosition);
		worldContext.logger.LogUnitMoved(worldContext.tick, unit.GetId(), newPosition);

		if (newPosition == _targetPosition) {
			worldContext.logger.LogMarchEnded(worldContext.tick, unit.GetId(), _targetPosition);
		}

		return Status::Success;
	}
} // namespace acid7beast::tbs
