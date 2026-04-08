#pragma once
#include <vector>

namespace dae
{
	enum class TileType
	{
		Dirt
		,Tunnel
		,Empty
	};

	class Grid
	{
	public:
		explicit Grid(int cols, int rows, float tileSize);

		TileType GetTile(int col, int row) const;
		void SetTileType(int col, int row, const TileType& type);

		bool IsInGrid(int col, int row) const;
		int GetCols() const;
		int GetRows() const;
		float GetTileSize() const;

	private:
		int m_rows{};
		int m_cols{};
		float m_tileSize{};

		std::vector<TileType> m_tiles;
	};
}
