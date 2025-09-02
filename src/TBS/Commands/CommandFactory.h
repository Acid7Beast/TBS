// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Units/Components/Behaviour/BehaviourVisitor.h>

namespace acid7beast::tbs
{
	template <typename CommandParams>
	class CommandFactory final : public BehaviourVisitor
	{
	public:
		CommandFactory(CommandParams&& params)
			: _params(std::move(params))
		{}

	public:
		inline void Visit(SwordsmanBehaviourComponent& behaviour) override;
		inline void Visit(HunterBehaviourComponent& behaviour) override;

	private:
		CommandParams _params;
	};
}  // namespace acid7beast::tbs
