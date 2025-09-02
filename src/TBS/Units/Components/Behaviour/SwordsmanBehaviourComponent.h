// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "BaseBehaviourComponent.h"

namespace acid7beast::tbs
{
	class SwordsmanBehaviourComponent final : public BaseBehaviourComponent
	{
	public:
		virtual void Visit(BehaviourVisitor& visitor) override { visitor.Visit(*this); };
	};
} // namespace acid7beast::tbs
