#include "PlayingState.h"

//scenes
#include "Scene/DiggerSceneManager.h"
#include "SceneManager.h"
#include "Scene/DiggerScene.h"
#include "GameObject.h"

//gamestate
#include "Scene/GameState/EndScreenState.h"
#include "Scene/GameState/StartScreenState.h"

//collision
#include "Collision/CollisionSystem.h"
#include "Scene/PointsComponent.h"
#include "Player/HealthComponent.h"

#include "TextComponent.h"
#include"Scene.h"
#include "ResourceManager.h"
void dae::PlayingState::OnEnter(DiggerSceneManager* pDiggerSceneManager)
{
	m_pDiggerSceneManager = pDiggerSceneManager;
}

void dae::PlayingState::LoadScene(DiggerSceneManager*)
{
	LoadNextLevel();

	//auto& scene = dae::SceneManager::GetInstance().CreateScene();
	//auto font = dae::ResourceManager::GetInstance().LoadFont("Resources/GameFont.ttf", 36);
	////instructions
	//SDL_Color white{ 255, 255, 255, 255 };
	//auto instructionP2 = std::make_unique<GameObject>();
	//instructionP2->SetLocalPosition({ 10.f, 500.f, 0.f });
	//auto* textP2 = instructionP2->AddComponent<TextComponent>(font, white);
	//textP2->SetText("Playing");
	//scene.Add(std::move(instructionP2));
}

void dae::PlayingState::OnExit(DiggerSceneManager* )
{
}

void dae::PlayingState::LoadNextLevel()
{
	if (m_currentLevelIndex >= m_Levels.size())
	{
		m_currentLevelIndex = 0;
	}

	LoadDiggerLevel(m_Levels[m_currentLevelIndex]);
	++m_currentLevelIndex;
}
void dae::PlayingState::LoadDiggerLevel(const LevelData& levelData)
{
	DiggerScene diggerScene{ levelData, m_pDiggerSceneManager };
	diggerScene.LoadScene();
	m_currentPlayer = diggerScene.GetPlayer();

	if (m_currentPlayer)
	{
		if (auto* score = m_currentPlayer->GetComponent<PointsComponent>())
			score->AddScore(m_currentScore);

		if (auto* health = m_currentPlayer->GetComponent<HealthComponent>())
		{
			health->Health(m_currentLives);
		}
	}
}
void dae::PlayingState::ResetCurrentLevel()
{
	LoadDiggerLevel(m_Levels[m_currentLevelIndex]);
}
void dae::PlayingState::ProccessNotificationsScenes(GameEvent event, DiggerSceneManager* pDiggerSceneManager)
{
	if (event == GameEvent::AllEmeraldsCollected)
	{
		SaveCurrentGameData();

		if (m_currentLevelIndex >= m_Levels.size())
		{
			pDiggerSceneManager->SetState(std::make_unique<EndScreenState>(true, m_currentScore));
		}
		else
		{
			SceneManager::GetInstance().SetPendingAction([this]() { LoadNextLevel(); });
		}
	}
	if (event == GameEvent::PlayerDied)
	{
		SaveCurrentGameData();
		if (m_currentLives <= 0)
		{
			pDiggerSceneManager->SetState(std::make_unique<EndScreenState>(false, m_currentScore));
		}
		else
		{
			SceneManager::GetInstance().SetPendingAction([this]() { ResetCurrentLevel(); });
		}
	}
}
void dae::PlayingState::SaveCurrentGameData()
{
	if (m_currentPlayer)
	{
		if (auto* score = m_currentPlayer->GetComponent<PointsComponent>())
			m_currentScore = score->GetScore();
		if (auto* health = m_currentPlayer->GetComponent<HealthComponent>())
		{
			m_currentLives = health->GetLives();
		}
	}
}
