#pragma once
#include "LevelData.h"
#include <vector>
#include "Observer.h"
#include "Scene/Event.h"
namespace dae
{
	class GameObject;
	class DiggerSceneManager final :public Observer<GameEvent>
	{
	public:
		explicit DiggerSceneManager();
		~DiggerSceneManager() = default;
		DiggerSceneManager(const DiggerSceneManager& other) = delete;
		DiggerSceneManager(DiggerSceneManager&& other) = delete;
		DiggerSceneManager& operator=(const DiggerSceneManager& other) = delete;
		DiggerSceneManager& operator=(DiggerSceneManager&& other) = delete;

		void LoadNextLevel();
		void ResetCurrentLevel();
		int GetScore()const { return m_currentScore; }
		int GetLives()const { return m_currentLives; }
	private:

		void LoadDiggerLevel(const LevelData& levelData);
		void InitSound() const;
		void InitInput();

		//next level observer
		virtual void Notify(GameEvent event, GameObject* gameObject) override;

		int m_currentLevelIndex{};
		int m_currentScore{};
		int m_currentLives{3};
		bool m_skipFirstFrame{ false };
		GameObject* m_currentPlayer{ nullptr }; //need to be a pointer because it doesnt own

		std::vector<LevelData> m_Levels{
		LevelData{"Data/Resources/Level02Test.txt"}
		,LevelData{"Data/Resources/Level02Test.txt"}
		,LevelData{"Data/Resources/Level02Test.txt"}
		};

	};

}