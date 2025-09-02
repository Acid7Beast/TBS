// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BehaviourVisitor.h"

#include <TBS/Common.h>
#include <TBS/Commands/BaseCommand.h>
#include <TBS/Units/Components/Common.h>

#include <memory>
#include <deque>

namespace acid7beast::tbs
{
	class Unit;
	struct WorldContext;

	class BaseBehaviourComponent
	{
	public:
		inline void SetOwner(Unit& owner) { _owner = &owner; }
		ActingState Act(WorldContext& worldContext);

	public:
		inline virtual void AddCommand(std::unique_ptr<BaseCommand> command) { _commands.push_back(std::move(command)); }
		inline void ClearCommands() { _commands.clear(); }
		virtual void Visit(BehaviourVisitor& visitor) = 0;
		inline bool HasCommands() const { return !_commands.empty(); }

	protected:
		Unit* _owner = nullptr;
		std::deque<std::unique_ptr<BaseCommand>> _commands;
	};

	class EmptyBehaviourComponent final : public BaseBehaviourComponent
	{
	public:
		void AddCommand(std::unique_ptr<BaseCommand> /*command*/) override {}
		void Visit(BehaviourVisitor& /*visitor*/) override {}
	};
} // namespace acid7beast::tbs
