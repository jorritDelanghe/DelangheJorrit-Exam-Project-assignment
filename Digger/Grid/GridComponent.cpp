#include "GridComponent.h"
#include "renderer.h"
#include "ResourceManager.h"
#include"DataTypes.h"
#include "Scene/LevelLoader.h"

dae::GridComponent::GridComponent(GameObject* pOwner, const std::string& filePath)
	:Component(pOwner)
{
	m_tileDataMap[TileType::DirtWall] = TileData{ ResourceManager::GetInstance().LoadTexture("Resources/dirt.png"), true};
	m_tileDataMap[TileType::Tunnel] = TileData{ ResourceManager::GetInstance().LoadTexture("Resources/tunnel.png"), true};
	m_tileDataMap[TileType::BorderWallGame] = TileData{ ResourceManager::GetInstance().LoadTexture("Resources/BorderWall.png"), true};

	LevelLoader levelLoader(filePath, m_grid); //needs to be temp object or else gets deleted for filling grid


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
dae::TileType dae::GridComponent::DiggedTile(int col, int row)
{

	TileType tempTileType = m_grid.GetTileType(col, row);

	m_grid.SetTileType(col, row, TileType::Tunnel); //set digged

	return tempTileType;
}
dae::TileType dae::GridComponent::DiggedTile(const Rect& boundingBox)
{
	TileType t{};
	for (const auto& [col, row] : GetCorners(boundingBox))
	{
		if (!m_grid.IsInGrid(col, row))continue;

		t = m_grid.GetTileType(col, row);
		if (t == TileType::DirtWall)
		{
			DiggedTile(col, row);
		}
	}
	return t;
}
dae::TileType dae::GridComponent::GetCollisionTileType(const Rect& boundingBox)
{
	//check if we need TileType return
	TileType t{};
	for (const auto& [col, row] : GetCorners(boundingBox))
	{
		if (!m_grid.IsInGrid(col, row)) return TileType::BorderWallGame;

		t = m_grid.GetTileType(col, row);

		if (   t == TileType::BorderWallGame
			|| t == TileType::DirtWall) //otherwise some dirtwalls are not getting registered
			return t; 
	}
	return t;
}
int dae::GridComponent::WorldToCol(float x) const
{
	return static_cast<int>(x / m_grid.GetTileSize());
}
int dae::GridComponent::WorldToRow(float y) const
{
	return static_cast<int>(y / m_grid.GetTileSize());
}

std::pair<int, int> dae::GridComponent::WorldToCell(float x, float y) const
{
	return std::pair<int, int>({ WorldToCol(x), WorldToRow(y)});
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

dae::Grid& dae::GridComponent::GetGridReference()
{
	return m_grid;
}

void dae::GridComponent::RenderTile(int col, int row) const
{
	std::shared_ptr<Texture2D> texture{};
	switch (m_grid.GetTileType(col, row))
	{
		case TileType::DirtWall:
			texture = m_tileDataMap.at(TileType::DirtWall).texture;
			break;
		case TileType::Tunnel:
			texture = m_tileDataMap.at(TileType::Tunnel).texture;
			break;
		case TileType::BorderWallGame:
			texture = m_tileDataMap.at(TileType::BorderWallGame).texture;
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

std::vector<std::pair<int, int>> dae::GridComponent::GetCorners(const Rect& boundingBox)
{
	std::vector<std::pair<int, int>> corners = {
		{WorldToCell(boundingBox.x, boundingBox.y)}
		, { WorldToCell(boundingBox.x + boundingBox.width, boundingBox.y) }
			, { WorldToCell(boundingBox.x, boundingBox.y + boundingBox.height)}
			, { WorldToCell(boundingBox.x + boundingBox.width, boundingBox.y + boundingBox.height) }
	};
	return corners;
}


