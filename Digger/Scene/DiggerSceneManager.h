#pragma once
#include "LevelData.h"
#include <vector>

namespace dae
{
	class DiggerSceneManager final
	{
	public:
		explicit DiggerSceneManager();
		~DiggerSceneManager() = default;
		DiggerSceneManager(const DiggerSceneManager& other) = delete;
		DiggerSceneManager(DiggerSceneManager&& other) = delete;
		DiggerSceneManager& operator=(const DiggerSceneManager& other) = delete;
		DiggerSceneManager& operator=(DiggerSceneManager&& other) = delete;

		void LoadNextLevel();
	private:

		void LoadDiggerLevel(const LevelData& levelData);
		void InitSound() const;
		void InitInput();

		int m_currentLevelIndex{};

		std::vector<LevelData> m_Levels{
		LevelData{"Data/Resources/Level01.txt"}
		,LevelData{"Data/Resources/Level02.txt"}
		,LevelData{"Data/Resources/Level03.txt"}
		};

	};

}