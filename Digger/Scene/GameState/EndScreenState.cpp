#include "EndScreenState.h"
#include "TextComponent.h"
#include"Scene.h"
#include "ResourceManager.h"
#include "SceneManager.h"

dae::EndScreenState::EndScreenState(bool hasWon, int score)
	:m_hasWon(hasWon)
	,m_score(score)
{
}

void dae::EndScreenState::OnEnter(DiggerSceneManager* )
{
}

void dae::EndScreenState::LoadScene(DiggerSceneManager*)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Resources/GameFont.ttf", 36);
	//instructions
	SDL_Color white{ 255, 255, 255, 255 };
	auto instructionP2 = std::make_unique<GameObject>();
	instructionP2->SetLocalPosition({ 10.f, 500.f, 0.f });
	auto* textP2 = instructionP2->AddComponent<TextComponent>(font, white);
	textP2->SetText(std::to_string(m_hasWon) + " " + std::to_string(m_score));
	scene.Add(std::move(instructionP2));

}

void dae::EndScreenState::OnExit(DiggerSceneManager* )
{
}
