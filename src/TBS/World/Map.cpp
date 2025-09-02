// (c) 2025 Acid7Beast. Use with wisdom.

#include "Map.h"

#include <TBS/Units/Unit.h>

#include <algorithm>
#include <iterator>
#include <ranges>

namespace acid7beast::tbs
{
	void Map::Create(const IVector2& size)
	{
		_width = size.x;
		_height = size.y;
		_cells.assign(_width * _height, std::vector<uint32_t>());
	}

	bool Map::IsValidPosition(const IVector2& pos) const
	{
		return pos.x >= 0 && pos.x < _width && pos.y >= 0 && pos.y < _height;
	}

	bool Map::IsCellOccupied(const IVector2& pos) const
	{
		return IsValidPosition(pos) && !_cells[pos.y * _width + pos.x].empty();
	}

	void Map::PlaceUnit(uint32_t unitId, const IVector2& pos)
	{
		if (IsValidPosition(pos)) {
			_cells[pos.y * _width + pos.x].push_back(unitId);
		}
	}

	void Map::RemoveUnit(uint32_t unitId, const IVector2& pos)
	{
		if (IsValidPosition(pos)) {
			auto& cellUnits = _cells[pos.y * _width + pos.x];
			auto it = std::find(cellUnits.begin(), cellUnits.end(), unitId);
			if (it != cellUnits.end()) {
				cellUnits.erase(it);
			}
		}
	}

	std::vector<Unit*> Map::GetUnitInRadius(
		const UnitTable& units, const IVector2& pos, int minRadius, int maxRadius) const
	{
		std::unordered_set<uint32_t> unitsInMaxRadius = GetUnitInRadius(units, pos, maxRadius);
		std::unordered_set<uint32_t> unitsInMinRadius = GetUnitInRadius(units, pos, minRadius);

		auto unitsInRadiusView = unitsInMaxRadius | std::views::filter([&](uint32_t unitId) { return !unitsInMinRadius.contains(unitId); })
								 | std::views::transform(
									 [&units](uint32_t unitId) -> Unit* {
										 auto it = units.find(unitId);
										 if (it != units.end()) {
											 return it->second.get();
										 }
										 return nullptr;
									 })
								 | std::views::filter(
									 [](Unit* unitPtr) {
										 return unitPtr != nullptr;
									 });

		return { unitsInRadiusView.begin(), unitsInRadiusView.end() };
	}

	std::unordered_set<uint32_t> Map::GetUnitInRadius(const UnitTable& units, const IVector2& pos, int radius) const
	{
		std::unordered_set<uint32_t> unitsInRadius;
		for (int dy = -radius; dy <= radius; ++dy) {
			for (int dx = -radius; dx <= radius; ++dx) {
				const IVector2 targetPos = { pos.x + dx, pos.y + dy };

				const int minBorderDistance = radius - std::max(std::abs(dx), std::abs(dy));

				if (IsValidPosition(targetPos)) {
					const auto& cellUnits = _cells[targetPos.y * _width + targetPos.x];

					for (int unitId : cellUnits) {
						auto unitIter = units.find(unitId);
						if (unitIter != units.cend()) {
							if (unitIter->second->Movement().GetGroundDistance() <= minBorderDistance) {
								unitsInRadius.insert(unitId);
							}
						}
					}
				}
			}
		}

		return unitsInRadius;
	}
} // namespace acid7beast::tbs
