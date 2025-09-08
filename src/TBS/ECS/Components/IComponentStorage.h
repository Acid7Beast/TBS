/// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/ECS/Common.h>

namespace acid7beast::tbs
{
	class IComponentStorage
	{
	public:
		virtual ~IComponentStorage() = default;
		virtual void RemoveComponent(EntityId entity) = 0;
	};
} // namespace acid7beast::tbs
