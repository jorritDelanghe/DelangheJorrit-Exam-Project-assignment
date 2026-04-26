#pragma once
#include "Component.h"
#include "GameObject.h"
#include "texture2D.h"
#include <memory>
#include"Grid.h"

namespace dae
{
	class GridComponent final : public Component
	{
	public:
		explicit GridComponent(GameObject*pOwner, const std::string& filePath);

		virtual void Render() const override;
		void DiggedTile(int col, int row);

		int WorldToCol(float x) const;
		int WorldToRow(float y) const;

		float ColToWorld(int col) const;
		float RowToWorld(int row) const;

		const Grid& GetGrid()const;

	private:
		dae::Grid m_grid{};

		std::shared_ptr<Texture2D> m_dirtTexture{};
		std::shared_ptr<Texture2D> m_tunnelTexture{};

		void RenderTile(int col, int row) const;
	};

}