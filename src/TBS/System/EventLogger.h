// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Common.h>

#include <stdint.h>
#include <string>

namespace acid7beast::tbs
{
	class BaseEventLogger
	{
	public:
		virtual ~BaseEventLogger() = default;

	public:
		virtual void LogMapCreated(uint64_t tick, const IVector2& size) = 0;
		virtual void LogMarchEnded(uint64_t tick, EntityId id, const IVector2& destination) = 0;
		virtual void LogMarchStarted(uint64_t tick, EntityId id, const IVector2& source, const IVector2& destination) = 0;
		virtual void LogEntityAttacked(uint64_t tick, EntityId attackerId, EntityId targetId, uint32_t damage, uint32_t targetHp) = 0;
		virtual void LogEntityDied(uint64_t tick, EntityId id) = 0;
		virtual void LogEntityMoved(uint64_t tick, EntityId id, const IVector2&) = 0;
		virtual void LogEntitySpawned(uint64_t tick, EntityId id, const std::string& unitType, const IVector2& position) = 0;
	};

	template<typename Logger>
	class EventLoggerWrapper final : public BaseEventLogger
	{
	public:
		EventLoggerWrapper(Logger& logger)
			: _logger(logger)
		{
		}

	public:
		inline void LogMapCreated(uint64_t tick, const IVector2& size) override;
		inline void LogMarchEnded(uint64_t tick, EntityId id, const IVector2& destination) override;
		inline void LogMarchStarted(uint64_t tick, EntityId id, const IVector2& source, const IVector2& destination) override;
		inline void LogEntityAttacked(uint64_t tick, EntityId attackerId, EntityId targetId, uint32_t damage, uint32_t targetHp) override;
		inline void LogEntityDied(uint64_t tick, EntityId id) override;
		inline void LogEntityMoved(uint64_t tick, EntityId id, const IVector2&) override;
		inline void LogEntitySpawned(uint64_t tick, EntityId id, const std::string& unitType, const IVector2& position) override;

	private:
		Logger& _logger;
	};
} // namespace acid7beast::tbs
