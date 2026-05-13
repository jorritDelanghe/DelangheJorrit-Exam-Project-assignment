#pragma once

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
	};
	struct GridPos
	{
		int col;
		int row;

		auto operator <=>(const GridPos&) const = default; // works on all comparison, version 20 and higher
	};
}