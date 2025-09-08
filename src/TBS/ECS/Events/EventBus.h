// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include "EventQueue.h"
#include "BaseEventStorage.h"

#include <unordered_map>
#include <memory>
#include <typeindex>

namespace acid7beast::tbs
{
	class EventBus final
	{
		// Public interface methods.
	public:
		template<typename EventType>
		inline void PushEvent(EventType&& event);

		template<typename EventType>
		inline void ClearEvents();
		
		template<typename EventType>
		inline std::vector<EventType>& GetEvents();

		// Private state members.
	private:
		std::unordered_map<std::type_index, std::unique_ptr<BaseEventStorage>> _eventQueue;
	};

	template<typename EventType>
	inline void EventBus::PushEvent(EventType&& event)
	{
		if (_eventQueue.find(std::type_index(typeid(EventType))) == _eventQueue.end()) {
			_eventQueue[std::type_index(typeid(EventType))] = std::make_unique<EventQueue<EventType>>();
		}

		static_cast<EventQueue<EventType>*>(_eventQueue.at(std::type_index(typeid(EventType))).get())->AddEvent(std::forward<EventType>(event));
	}

	template<typename EventType>
	inline void EventBus::ClearEvents()
	{
		if (_eventQueue.find(std::type_index(typeid(EventType))) == _eventQueue.end()) {
			return;
		}

		static_cast<EventQueue<EventType>*>(_eventQueue.at(std::type_index(typeid(EventType))).get())->ClearEvents();
	}

	template<typename EventType>
	inline std::vector<EventType>& EventBus::GetEvents()
	{
		if (_eventQueue.find(std::type_index(typeid(EventType))) == _eventQueue.end()) {
			_eventQueue[std::type_index(typeid(EventType))] = std::make_unique<EventQueue<EventType>>();
		}

		return static_cast<EventQueue<EventType>*>(_eventQueue.at(std::type_index(typeid(EventType))).get())->GetEvents();
	}
} // namespace acid7beast::tbs