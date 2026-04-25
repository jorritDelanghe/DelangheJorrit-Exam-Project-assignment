#include "GridComponent.h"
#include "renderer.h"
#include "ResourceManager.h"
#include"DataTypes.h"
#include "LevelLoader.h"

dae::GridComponent::GridComponent(GameObject* pOwner, const std::string& filePath)
	:Component(pOwner)
{
	LevelLoader(filePath, m_grid);
	m_dirtTexture = ResourceManager::GetInstance().LoadTexture("Resources/dirt.png");
	m_tunnelTexture = ResourceManager::GetInstance().LoadTexture("Resources/tunnel.png");
}

void dae::GridComponent::Render() const
{
	//no render component otherwise needs gameobject for each tile, to avoid custom render
	for (int r{}; r < m_grid.GetRows(); ++r)
	{
		for(int c{}; c< m_grid.GetCols(); ++c)
		{
			RenderTile(c, r);
		}
	}

}
void dae::GridComponent::DiggedTile(int col, int row)
{
	m_grid.SetTileType(col, row, TileType::Tunnel);
}

int dae::GridComponent::WorldToCol(float x) const
{
	return static_cast<int>(x / m_grid.GetTileSize());
}
int dae::GridComponent::WorldToRow(float y) const
{
	return static_cast<int>(y / m_grid.GetTileSize());
}

float dae::GridComponent::ColToWorld(int col) const
{
	return col * m_grid.GetTileSize();
}
float dae::GridComponent::RowToWorld(int row) const
{
	return row * m_grid.GetTileSize();
}

const dae::Grid& dae::GridComponent::GetGrid()const
{
	return m_grid;
}

void dae::GridComponent::RenderTile(int col, int row) const
{
	std::shared_ptr<Texture2D> texture{};

	switch (m_grid.GetTile(col, row))
	{
		case TileType::DirtWall:
			texture = m_dirtTexture;
			break;
		case TileType::Tunnel:
			texture = m_tunnelTexture;
			break;
		default:
			return;
	}

	Renderer::GetInstance().RenderTexture(
		*texture
		, ColToWorld(col)
		, RowToWorld(row)
		, m_grid.GetTileSize()
		, m_grid.GetTileSize()
	);
}


