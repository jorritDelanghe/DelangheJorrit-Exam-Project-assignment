#pragma once
#include <compare>

namespace dae
{
	enum class TileType
	{
		Empty
		, DirtWall
		, Tunnel
		, Emerald
		, GoldBag
		, EnemySpawn
		, BorderWallGame
		, PlayerStart
	};
	struct GridPos
	{
		int col{};
		int row{};

		auto operator <=>(const GridPos&) const = default; // works on all comparison, version 20 and higher
	};
	inline GridPos indexToGridPos(int index, int maxCols)
	{
		return dae::GridPos{
		index % maxCols
	,	 index / maxCols };
	}

	struct Rect
	{
		float x{};
		float y{};
		float width{};
		float height{};
	};


	struct Size
	{
		float width{};
		float height{};
	};
}