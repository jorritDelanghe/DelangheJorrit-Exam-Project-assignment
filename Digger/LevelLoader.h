#pragma once
#include <vector>
#include "DataTypes.h"
#include "Grid.h"
#include <unordered_map>
namespace dae
{
	class LevelLoader final
	{
	public:
		LevelLoader(const std::string& filePath, std::unordered_map<TileType, TileData>& tileDataMap, Grid& grid);

	private:
		void loadLevelFromFile(const std::string& filePath, std::unordered_map<TileType, TileData>& tileDataMap, Grid& grid);
	};

}