// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <vector>
#include "BaseEventStorage.h"

namespace acid7beast::tbs
{
	template<typename EventType>
	class EventQueue final : public BaseEventStorage
	{
		// Public interface methods.
	public:
		inline void AddEvent(EventType&& event);
		inline void ClearEvents() override;

		inline std::vector<EventType>& GetEvents() { return _events; }

		// Private state members.
	private:
		std::vector<EventType> _events;
	};

	template<typename EventType>
	inline void EventQueue<EventType>::AddEvent(EventType&& event)
	{
		_events.push_back(std::forward<EventType>(event));
	}

	template<typename EventType>
	inline void EventQueue<EventType>::ClearEvents()
	{
		_events.clear();
	}
} // namespace acid7beast::tbs