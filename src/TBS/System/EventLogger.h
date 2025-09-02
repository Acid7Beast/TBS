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
		virtual void LogMarchEnded(uint64_t tick, uint32_t unitId, const IVector2& destination) = 0;
		virtual void LogMarchStarted(uint64_t tick, uint32_t unitId, const IVector2& source, const IVector2& destination) = 0;
		virtual void LogUnitAttacked(uint64_t tick, uint32_t attackerUnitId, uint32_t targetUnitId, uint32_t damage, uint32_t targetHp) = 0;
		virtual void LogUnitDied(uint64_t tick, uint32_t unitId) = 0;
		virtual void LogUnitMoved(uint64_t tick, uint32_t unitId, const IVector2&) = 0;
		virtual void LogUnitSpawned(uint64_t tick, uint32_t unitId, const std::string& unitType, const IVector2& position) = 0;
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
		inline void LogMarchEnded(uint64_t tick, uint32_t unitId, const IVector2& destination) override;
		inline void LogMarchStarted(uint64_t tick, uint32_t unitId, const IVector2& source, const IVector2& destination) override;
		inline void LogUnitAttacked(uint64_t tick, uint32_t attackerUnitId, uint32_t targetUnitId, uint32_t damage, uint32_t targetHp) override;
		inline void LogUnitDied(uint64_t tick, uint32_t unitId) override;
		inline void LogUnitMoved(uint64_t tick, uint32_t unitId, const IVector2&) override;
		inline void LogUnitSpawned(uint64_t tick, uint32_t unitId, const std::string& unitType, const IVector2& position) override;

	private:
		Logger& _logger;
	};
} // namespace acid7beast::tbs
