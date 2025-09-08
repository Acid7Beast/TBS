// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Common.h>

#include <TBS/ECS/Components/Unit/Common.h>
#include <TBS/ECS/Components/Unit/Behaviour/Commands/BaseCommand.h>

#include <memory>
#include <deque>

namespace acid7beast::tbs
{
	class Registry;
	struct WorldContext;

	class BehaviourComponent final
	{
		// Life-circle management.
	public:
		BehaviourComponent();
		BehaviourComponent(const BehaviourComponent&) = delete;
		BehaviourComponent& operator=(const BehaviourComponent&) = delete;
		BehaviourComponent(BehaviourComponent&&) noexcept;
		BehaviourComponent& operator=(BehaviourComponent&&) noexcept;

		// Public interface methods.
	public:
		ActingState Act(Registry& registry, WorldContext& worldContext, EntityId id);
		inline void AddCommand(std::unique_ptr<BaseCommand> command) { _commands.push_back(std::move(command)); }
		inline void ClearCommands() { _commands.clear(); }
		inline bool HasCommands() const { return !_commands.empty(); }

		// Private state members.
	private:
		std::deque<std::unique_ptr<BaseCommand>> _commands;
	};
} // namespace acid7beast::tbs
