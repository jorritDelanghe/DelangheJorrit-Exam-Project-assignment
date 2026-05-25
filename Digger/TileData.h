#pragma once
#include <memory>
#include "texture2D.h"
#include "DataTypes.h"

//flyweight pattern
//jorrit side note:a bit over the top for not so much data but it is a place where the pattern can be applied and it is easy to make bigger 

namespace dae
{
	struct TileData
	{
		std::shared_ptr<dae::Texture2D> texture{};
		bool isTunnel{ false };
		dae::TileType tileType{ dae::TileType::Empty };
	};
}