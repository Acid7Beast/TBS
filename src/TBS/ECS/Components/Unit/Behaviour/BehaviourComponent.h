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

	struct BehaviourComponent final
	{
		std::deque<std::unique_ptr<BaseCommand>> commands;
		
		// Default constructor
		BehaviourComponent() = default;
		
		// Copy constructor - deleted because unique_ptr is not copyable
		BehaviourComponent(const BehaviourComponent&) = delete;
		
		// Copy assignment - deleted because unique_ptr is not copyable
		BehaviourComponent& operator=(const BehaviourComponent&) = delete;
		
		// Move constructor
		BehaviourComponent(BehaviourComponent&& other) noexcept
			: commands(std::move(other.commands))
		{}
		
		// Move assignment
		BehaviourComponent& operator=(BehaviourComponent&& other) noexcept
		{
			if (this != &other) {
				commands = std::move(other.commands);
			}
			return *this;
		}
	};
} // namespace acid7beast::tbs
