#pragma once
#include <vector>
#include <string>
#include "DataTypes.h"

namespace dae
{
	class Grid
	{
	public:
		Grid() = default; //problem otherwise in gridcomponent with intializing
		explicit Grid(int cols, int rows, float tileSize,const std::vector<TileType>& tiles);

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
