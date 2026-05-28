#pragma once
#include "Component.h"
#include "GameObject.h"
#include "texture2D.h"
#include <memory>
#include"Grid.h"
#include <unordered_map>
#include "TileData.h"
#include <algorithm>
namespace dae
{
	class GridComponent final : public Component
	{
	public:
		explicit GridComponent(GameObject*pOwner, const std::string& filePath);

		virtual void Render() const override;
		TileType DiggedTile(int col, int row);
		TileType DiggedTile(const Rect& boundingBox);
		TileType GetCollisionTileType(const Rect& boundingBox);

		int WorldToCol(float x) const;
		int WorldToRow(float y) const;
		std::pair<int, int>WorldToCell(float x, float y)const;

		float ColToWorld(int col) const;
		float RowToWorld(int row) const;

		const Grid& GetGrid()const;

	private:
		dae::Grid m_grid{};
		std::unordered_map<TileType, TileData> m_tileDataMap{};
		void RenderTile(int col, int row) const;
		std::vector<std::pair<int,int>> GetCorners(const Rect& boundingBox);
	};

}