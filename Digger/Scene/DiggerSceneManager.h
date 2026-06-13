#pragma once
#include "LevelData.h"
#include <vector>
#include "Observer.h"
#include "Scene/Event.h"

//gamestate
#include "GameState/GameState.h"
#include <memory>
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

		void LoadScreen();
		int GetScore()const { return m_currentScore; }
		int GetLives()const { return m_currentLives; }
		void SetState(std::unique_ptr<GameState> newState); //needed in states

		//next level observer
		virtual void Notify(GameEvent event, GameObject* gameObject) override;
	private:

		void LoadDiggerLevel(const LevelData& levelData);
		void InitSound() const;
		void InitInput();
		//save
		void SaveCurrentGameData();

		int m_currentScore{};
		int m_currentLives{4};

		GameObject* m_currentPlayer{ nullptr }; //need to be a pointer because it doesnt own

		std::unique_ptr<GameState> m_currentGameState{nullptr};


	};

}