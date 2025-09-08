// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/ECS/Common.h>

#include <vector>

namespace acid7beast::tbs
{
	class BaseEventStorage
	{
		// Life-circle management.
	public:
		virtual ~BaseEventStorage() = default;

		// Public virtualinterface methods.
	public:
		virtual void ClearEvents() = 0;
	};
} // namespace acid7beast::tbs
