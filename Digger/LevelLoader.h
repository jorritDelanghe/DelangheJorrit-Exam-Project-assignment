#pragma once
#include <vector>
#include "DataTypes.h"
#include "Grid.h"

namespace dae
{
	class LevelLoader final
	{
	public:
		LevelLoader(const std::string& filePath, Grid& grid);

	private:
		void loadLevelFromFile(const std::string& filePath,Grid& grid);
	};

}