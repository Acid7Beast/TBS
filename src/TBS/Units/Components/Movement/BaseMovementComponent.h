// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Common.h>
#include <TBS/Units/Components/Common.h>

namespace acid7beast::tbs
{
	class Unit;
	struct WorldContext;

	class BaseMovementComponent
	{
	public:
		BaseMovementComponent(const IVector2& position);
		virtual ~BaseMovementComponent() = default;

	public:
		inline void SetOwner(Unit& owner) { _owner = &owner; }
		void RemoveFromWorld(WorldContext& worldContext);
		void MoveTo(WorldContext& worldContext, const IVector2& newPosition);
		const IVector2& GetPosition() const { return _position; }

	public:
		virtual int GetGroundDistance() const = 0;
		virtual int GetMovementSpeed() const = 0;
		virtual MovementType GetMovementType() const = 0;
		virtual MovementState GetMovementState() const = 0;

	protected:
		Unit* _owner = nullptr;
		IVector2 _position;
	};

	class EmptyMovementComponent final : public BaseMovementComponent
	{
	public:
		EmptyMovementComponent(const IVector2& position);

	public:
		inline int GetMovementSpeed() const override { return 0; }
		inline int GetGroundDistance() const override {return 0; }
		inline MovementType GetMovementType() const override { return MovementType::Ground;}
		inline MovementState GetMovementState() const override {return MovementState::Building; }
	};
} // namespace acid7beast::tbs
