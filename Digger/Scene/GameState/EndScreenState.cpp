#include "EndScreenState.h"
#include "TextComponent.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Scene/Commands/ChangeLetterCommand.h"
#include "Scene/Commands/NextLetterCommand.h"
#include "Scene/Commands/ConfirmNameCommand.h"

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
		// Instruction
		auto instrObj = std::make_unique<GameObject>();
		instrObj->SetLocalPosition({ 10.f, 120.f, 0.f });
		auto* instructionText = instrObj->AddComponent<TextComponent>(smallFont, white);
		instructionText->SetText("NEW HIGHSCORE! Enter your name (Arrows: change letter, Enter: confirm)");
		scene.Add(std::move(instrObj));

		// Name entry display
		auto nameObj = std::make_unique<GameObject>();
		nameObj->SetLocalPosition({ 10.f, 170.f, 0.f });
		m_nameHighScore = nameObj->AddComponent<TextComponent>(font, white);
		scene.Add(std::move(nameObj));

		//controls
		input.BindKeyboardCommand(SDL_SCANCODE_RIGHT, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<ChangeLetterCommand>(m_nameHighScore, 1));

		input.BindKeyboardCommand(SDL_SCANCODE_LEFT, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<ChangeLetterCommand>(m_nameHighScore, -1));

		input.BindKeyboardCommand(SDL_SCANCODE_TAB, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<NextLetterCommand>(m_nameHighScore, 3));

		input.BindKeyboardCommand(SDL_SCANCODE_RETURN, InputManager::TriggerType::IsDownThisFrame,
			std::make_unique<ConfirmNameCommand>(m_nameHighScore, &m_highScoreManager, m_score));
	}

}

void dae::EndScreenState::OnExit(DiggerSceneManager* )
{
}
