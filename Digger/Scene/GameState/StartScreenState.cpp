#include "StartScreenState.h"

//input
#include <SDL3/SDL.h>
#include "InputManager.h"
#include "Scene/Commands/SetNewGameStateCommand.h"
#include "Scene/GameState/PlayingState.h"
#include "SceneManager.h"

//scene
#include "TextComponent.h"
#include"Scene.h"
#include "ResourceManager.h"

void dae::StartScreenState::OnEnter(DiggerSceneManager* pDiggerSceneManger)
{
	initInput(pDiggerSceneManger);
}
void dae::StartScreenState::LoadScene(DiggerSceneManager*)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Resources/GameFont.ttf", 36);
	SDL_Color white{ 255, 255, 255, 255 };

	//instructions

	auto titleObj = std::make_unique<GameObject>();
	titleObj->SetLocalPosition({ 10.f, 50.f, 0.f });
	auto* titleText = titleObj->AddComponent<TextComponent>(font, white);
	titleText->SetText("Digger");
	scene.Add(std::move(titleObj));

	auto instructionP2 = std::make_unique<GameObject>();
	instructionP2->SetLocalPosition({ 10.f, 100.f, 0.f });
	auto* textP2 = instructionP2->AddComponent<TextComponent>(font, white);
	textP2->SetText("Move WASD, arrows, controller");
	scene.Add(std::move(instructionP2));

	auto instructionP3 = std::make_unique<GameObject>();
	instructionP3->SetLocalPosition({ 10.f, 150.f, 0.f });
	auto* textP3 = instructionP3->AddComponent<TextComponent>(font, white);
	textP3->SetText("Press Space to start");
	scene.Add(std::move(instructionP3));


}
void dae::StartScreenState::OnExit(DiggerSceneManager* )
{
	SceneManager::GetInstance().SetPendingAction([this]() {
		InputManager::GetInstance().UnbindKeyboardCommand(SDL_SCANCODE_SPACE);
		});
}

void dae::StartScreenState::initInput(DiggerSceneManager* pDiggerSceneManger)
{
	//control
	InputManager::GetInstance().BindKeyboardCommand(SDL_SCANCODE_SPACE,
		InputManager::TriggerType::IsDownThisFrame,
		std::make_unique<SetNewGameStateCommand>(pDiggerSceneManger,std::make_unique<PlayingState>()));
}