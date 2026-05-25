#include "LevelLoader.h"

#ifdef _WIN32
#include <windows.h>
#endif

//file loading
#include <fstream>
#include <stdexcept>
#include <string>
#include <windows.h>

#include "TileData.h"

dae::LevelLoader::LevelLoader(const std::string& filePath,std::unordered_map<TileType,TileData>& tileDataMap, Grid& grid)
{
	loadLevelFromFile(filePath, tileDataMap,grid); //two times reference is that heavy?????
}

void dae::LevelLoader::loadLevelFromFile(const std::string& filePath, std::unordered_map<TileType,TileData>& tileDataMap, Grid& grid)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		OutputDebugStringA(("Could not open file: " + filePath + "\n").c_str());
		throw std::runtime_error("Could not open file: " + filePath);
	}
	int cols{};
	int rows{};
	float tileSize{};
	std::vector<TileData*> tiles;

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		if(line.rfind("TileSize:",0) == 0)
		{
			tileSize = std::stof(line.substr(9));
			continue;
		}
		if (cols == 0)
		{
			cols = static_cast<int>(line.size());
		}

		for (char character : line)
		{
			switch (character)
			{
			case '#':
				tiles.push_back(&tileDataMap.at(TileType::DirtWall));
				break;
			case '.':
				tiles.push_back(&tileDataMap.at(TileType::Tunnel));
				break;
			case'G':
				tiles.push_back(&tileDataMap.at(TileType::Tunnel));
				break;
			case'E':
				tiles.push_back(&tileDataMap.at(TileType::Tunnel));
				break;
			case'N':
				tiles.push_back(&tileDataMap.at(TileType::Tunnel));
				break;

			}
		}
		++rows;
	}
	grid = Grid(cols, rows, tileSize, tiles);
	OutputDebugStringA((std::to_string(cols) + "\n").c_str());
	OutputDebugStringA((std::to_string(rows) + "\n").c_str());
	OutputDebugStringA((std::to_string(tileSize) + "\n").c_str());
}
