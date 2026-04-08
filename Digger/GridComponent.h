#pragma once
#include "Grid.h"
#include "Component.h"
#include "GameObject.h"
#include "texture2D.h"
#include <memory>
namespace dae
{
	class GridComponent final : public Component
	{
		explicit GridComponent(GameObject*pOwner, int cols, int rows, float tileSize);

		virtual void Render() override const;
		void DiggedTile(int col, int row);

		int WorldToCol(float x) const;
		int WorldToRow(float y) const;

		float ColToWorld(int col) const;
		float RowToWorld(int row) const;

		const Grid& GetGrid()const;

	private:
		Grid m_grid{};

		std::shared_ptr<Texture2D> m_dirtTexture{};
		std::sahred_ptr<Texture2D> m_tunnelTexture{};

		void RenderTile(int col, int row) const;
	};

}