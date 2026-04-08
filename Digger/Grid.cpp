#include "Grid.h"

dae::Grid::Grid(int cols, int rows, float tileSize)
	:m_cols(cols)
	,m_rows(rows)
	,m_tileSize(tileSize)
	,m_tiles(cols * rows, TileType::Dirt)
{
}

dae::TileType dae::Grid::GetTile(int col, int row) const
{
	if (!IsInGrid(row, col)) return TileType::Empty;
	return m_tiles[(row * m_cols) + col];
}

void dae::Grid::SetTileType(int col, int row, const TileType& type)
{
	if (!IsInGrid(row, col)) return;
	m_tiles[row * m_cols + col] = type;
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
