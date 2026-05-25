#include "Grid.h"


dae::Grid::Grid(int cols, int rows, float tileSize, const std::vector<TileData*>& tiles)
	:m_cols(cols)
	,m_rows(rows)
	,m_tileSize(tileSize)
	,m_tiles(tiles)
{

}

dae::TileData dae::Grid::GetTileData(int col, int row) const
{
	if (!IsInGrid(col, row)) return TileData{};
	return *m_tiles[(row * m_cols) + col];
}

dae::TileType dae::Grid::GetTileType(int col, int row) const
{
	if (!IsInGrid(col, row)) return TileType::Empty;
	return m_tiles[(row * m_cols) + col]->tileType;
}

void dae::Grid::SetTileType(int col, int row, const TileType& type)
{
	if (!IsInGrid(col, row)) return;
	m_tiles[row * m_cols + col]->tileType = type;
}

bool dae::Grid::IsInGrid(int col, int row) const
{
	if (row * m_cols + col < m_cols * m_rows
		&& row >= 0
		&& col >= 0)
	{
		return true;
	}

	return false;
}

int dae::Grid::GetCols() const
{
	return m_cols;
}

int dae::Grid::GetRows() const
{
	return m_rows;
}

float dae::Grid::GetTileSize() const
{
	return m_tileSize;
}
