// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/System/EventLogger.h>

#include <IO/System/EventLog.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>

namespace acid7beast::tbs
{
	template<>
	inline void EventLoggerWrapper<sw::EventLog>::LogMapCreated(uint64_t tick, const IVector2& size)
	{
		_logger.log(tick, sw::io::MapCreated { static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y) });
	}

	template<>
	inline void EventLoggerWrapper<sw::EventLog>::LogMarchEnded(uint64_t tick, uint32_t unitId, const IVector2& destination)
	{
		_logger.log(tick, sw::io::MarchEnded { unitId, static_cast<uint32_t>(destination.x), static_cast<uint32_t>(destination.y) });
	}

	template<>
	inline void EventLoggerWrapper<sw::EventLog>::LogMarchStarted(uint64_t tick, uint32_t unitId, const IVector2& source, const IVector2& destination)
	{
		_logger.log(tick, sw::io::MarchStarted { unitId, static_cast<uint32_t>(source.x), static_cast<uint32_t>(source.y), static_cast<uint32_t>(destination.x), static_cast<uint32_t>(destination.y) });
	}

	template<>
	inline void EventLoggerWrapper<sw::EventLog>::LogUnitAttacked(uint64_t tick, uint32_t attackerUnitId, uint32_t targetUnitId, uint32_t damage, uint32_t targetHp)
	{
		_logger.log(tick, sw::io::UnitAttacked { attackerUnitId, targetUnitId, damage, targetHp });
	}

	template<>
	inline void EventLoggerWrapper<sw::EventLog>::LogUnitDied(uint64_t tick, uint32_t unitId)
	{
		_logger.log(tick, sw::io::UnitDied { unitId });
	}

	template<>
	inline void EventLoggerWrapper<sw::EventLog>::LogUnitMoved(uint64_t tick, uint32_t unitId, const IVector2& newPosition)
	{
		_logger.log(tick, sw::io::UnitMoved { unitId, static_cast<uint32_t>(newPosition.x), static_cast<uint32_t>(newPosition.y) });
	}

	template<>
	inline void EventLoggerWrapper<sw::EventLog>::LogUnitSpawned(uint64_t tick, uint32_t unitId, const std::string& unitType, const IVector2& position)
	{
		_logger.log(tick, sw::io::UnitSpawned { unitId, unitType, static_cast<uint32_t>(position.x), static_cast<uint32_t>(position.y) });
	}
} // namespace acid7beast::tbs
