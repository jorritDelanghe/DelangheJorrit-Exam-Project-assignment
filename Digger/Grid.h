#pragma once
#include <vector>
#include <string>
#include "DataTypes.h"
#include "TileData.h"

namespace dae
{
	class Grid
	{
	public:
		Grid() = default; //problem otherwise in gridcomponent with intializing
		explicit Grid(int cols, int rows, float tileSize,const std::vector<TileData*>& tiles);

		TileData GetTileData(int col, int row) const;
		TileType GetTileType(int col, int row) const;
		void SetTileType(int col, int row, const TileType& type);

		bool IsInGrid(int col, int row) const;
		int GetCols() const;
		int GetRows() const;
		float GetTileSize() const;


	private:
		int m_cols{};
		int m_rows{};
		float m_tileSize{};

		std::vector<TileData*> m_tiles;
	};
}
