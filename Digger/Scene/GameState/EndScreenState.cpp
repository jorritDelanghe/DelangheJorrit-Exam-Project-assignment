#include "EndScreenState.h"

//scene
#include "TextComponent.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "SceneManager.h"

//input
#include "InputManager.h"

//commands
#include "Scene/Commands/ChangeLetterCommand.h"
#include "Scene/Commands/NextLetterCommand.h"
#include "Scene/Commands/ConfirmNameCommand.h"
#include "Scene/Commands/SetNewGameStateCommand.h"
#include "Scene/GameState/StartScreenState.h"

dae::EndScreenState::EndScreenState(bool hasWon, int score)
	:m_hasWon(hasWon)
	,m_score(score)
{
}

void dae::EndScreenState::OnEnter(DiggerSceneManager* )
{
	InputManager::GetInstance().UnbindAll();
}

void dae::EndScreenState::LoadScene(DiggerSceneManager* pDiggerSceneManger)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Resources/GameFont.ttf", 36);
	auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Resources/GameFont.ttf", 24);
	auto& input = InputManager::GetInstance();
	SDL_Color white{ 255, 255, 255, 255 };

	// Title: won/lost + score
	auto resultObj = std::make_unique<GameObject>();
	resultObj->SetLocalPosition({ 10.f, 50.f, 0.f });
	auto* resultText = resultObj->AddComponent<TextComponent>(font, white);
	resultText->SetText((m_hasWon ? std::string("YOU WIN!") : std::string("GAME OVER")) +
		"  Score: " + std::to_string(m_score));
	scene.Add(std::move(resultObj));

	if (m_highScoreManager.CheckIfHighScore(m_score))
	{
		// Instruction1
		auto instrObj = std::make_unique<GameObject>();
		instrObj->SetLocalPosition({ 10.f, 120.f, 0.f });
		auto* instructionText = instrObj->AddComponent<TextComponent>(smallFont, white);
		instructionText->SetText("NEW HIGHSCORE! Enter your name!");
		scene.Add(std::move(instrObj));

		// Instruction2
		auto instrObj2 = std::make_unique<GameObject>();
		instrObj2->SetLocalPosition({ 10.f, 170.f, 0.f });
		auto* instructionText2 = instrObj2->AddComponent<TextComponent>(smallFont, white);
		instructionText2->SetText(" (Arrows/DpadLeft-right: change letter, TAB/DpadDown next letter, X/DpadUp: confirm)");
		scene.Add(std::move(instrObj2));

		// Name entry display
		auto nameObj = std::make_unique<GameObject>();
		nameObj->SetLocalPosition({ 10.f, 220.f, 0.f });
		auto* text = nameObj->AddComponent<TextComponent>(font, white);
		text->SetText("A");
	    auto* rawNameDisplay = nameObj.get();
		scene.Add(std::move(nameObj));

		//controls keys
		input.BindKeyboardCommand(SDL_SCANCODE_RIGHT, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<ChangeLetterCommand>(rawNameDisplay->GetComponent<TextComponent>(), 1));

		input.BindKeyboardCommand(SDL_SCANCODE_LEFT, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<ChangeLetterCommand>(rawNameDisplay->GetComponent<TextComponent>(), -1));

		input.BindKeyboardCommand(SDL_SCANCODE_TAB, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<NextLetterCommand>(rawNameDisplay->GetComponent<TextComponent>(), 3));

		input.BindKeyboardCommand(SDL_SCANCODE_X, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<ConfirmNameCommand>(rawNameDisplay->GetComponent<TextComponent>(), &m_highScoreManager, m_score));

		//controls
		input.BindControllerCommand(dae::GamepadButton::DpadRight, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<ChangeLetterCommand>(rawNameDisplay->GetComponent<TextComponent>(), 1));

		input.BindControllerCommand(dae::GamepadButton::DpadLeft, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<ChangeLetterCommand>(rawNameDisplay->GetComponent<TextComponent>(), -1));

		input.BindControllerCommand(dae::GamepadButton::DpadDown, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<NextLetterCommand>(rawNameDisplay->GetComponent<TextComponent>(), 3));

		input.BindControllerCommand(dae::GamepadButton::DpadUp, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<ConfirmNameCommand>(rawNameDisplay->GetComponent<TextComponent>(), &m_highScoreManager, m_score));
	}

	// go back To Start instuction
	auto instrObj3 = std::make_unique<GameObject>();
	instrObj3->SetLocalPosition({ 10.f, 170.f, 0.f });
	auto* instructionText3 = instrObj3->AddComponent<TextComponent>(smallFont, white);
	instructionText3->SetText(" Press Space To Go back To startScreen");
	scene.Add(std::move(instrObj3));

	InputManager::GetInstance().BindKeyboardCommand(SDL_SCANCODE_SPACE,
		InputManager::TriggerType::IsDownThisFrame,
		std::make_unique<SetNewGameStateCommand>(pDiggerSceneManger, std::make_unique<StartScreenState>()));
}

void dae::EndScreenState::OnExit(DiggerSceneManager* )
{
	SceneManager::GetInstance().SetPendingAction([this]() {
		InputManager::GetInstance().UnbindAll();
		});
}
