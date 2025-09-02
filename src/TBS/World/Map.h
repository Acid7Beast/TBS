// (c) 2025 Acid7Beast. Use with wisdom.
#pragma once

#include <TBS/Common.h>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace acid7beast::tbs
{
	class Unit;

	class Map final
	{
	public:
		void Create(const IVector2& size);
		bool IsValidPosition(const IVector2& pos) const;
		bool IsCellOccupied(const IVector2& pos) const;
		void PlaceUnit(uint32_t unitId, const IVector2& pos);
		void RemoveUnit(uint32_t unitId, const IVector2& pos);
		std::vector<Unit*> GetUnitInRadius(const UnitTable& units, const IVector2& pos, int minRadius, int maxRadius) const;

	private:
		std::unordered_set<uint32_t> GetUnitInRadius(const UnitTable& units, const IVector2& pos, int radius) const;

	private:
		uint32_t _width = 0, _height = 0;
		std::vector<std::vector<uint32_t>> _cells;
	};
} // namespace acid7beast::tbs
