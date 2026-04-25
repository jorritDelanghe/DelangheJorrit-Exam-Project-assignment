#include "LevelLoader.h"

//file loading
#include <fstream>
#include <stdexcept>
#include <string>

dae::LevelLoader::LevelLoader(const std::string& filePath, Grid& grid)
{
	loadLevelFromFile(filePath, grid); //two times reference is that heavy?????
}

void dae::LevelLoader::loadLevelFromFile(const std::string& filePath, Grid& grid)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file: " + filePath);
	}
	int cols{};
	int rows{};
	float tileSize{};
	std::vector<dae::TileType> tiles;

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		if (cols == 0)
		{
			cols = static_cast<int>(line.size());
		}

		if(line == "TileSize:")
		{
			std::getline(file, line);
			tileSize = std::stof(line);
			continue;
		}
		for (char character : line)
		{
			switch (character)
			{
			case '#':
				tiles.push_back(dae::TileType::DirtWall);
				break;
			case '.':
				tiles.push_back(dae::TileType::Tunnel);
				break;
			case'G':
				tiles.push_back(dae::TileType::GoldBag);
				break;
			case'E':
				tiles.push_back(dae::TileType::Emerald);
				break;

			}
		}
		++rows;
	}
	grid = Grid(cols, rows, tileSize, tiles);
}
