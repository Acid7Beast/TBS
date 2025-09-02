// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <type_traits>

namespace acid7beast::tbs
{
	class SwordsmanBehaviourComponent;
	class HunterBehaviourComponent;

	class BehaviourVisitor
	{
	public:
		virtual ~BehaviourVisitor() = default;

	public:
		virtual void Visit(SwordsmanBehaviourComponent& behaviour) = 0;
		virtual void Visit(HunterBehaviourComponent& behaviour) = 0;
	};
} // namespace acid7beast::tbs
