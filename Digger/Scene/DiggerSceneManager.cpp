
#include "DiggerSceneManager.h"

//sound
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

//input
#include <SDL3/SDL.h> //needs to be above inputmanager otherwise it doesnt know it
#include "InputManager.h"
#include "Commands/MuteSoundCommand.h"
#include "Commands/SkipToNextLevelCommand.h"
#include "SceneManager.h"

//gamestate
#include "Scene/GameState/EndScreenState.h"
#include "Scene/GameState/PlayingState.h"
#include "Scene/GameState/StartScreenState.h"

dae::DiggerSceneManager::DiggerSceneManager()
{
	InitSound(); //all sounds for the game
	InitInput();
	SetState(std::make_unique<EndScreenState>(true, 800));
}


void dae::DiggerSceneManager::LoadScreen()
{
	m_currentGameState->LoadScene(this);
}
void dae::DiggerSceneManager::InitSound() const
{
	ServiceLocator::RegisterSounSystem(std::make_unique<SDLSoundSystem>());
	ServiceLocator::GetSoundSystem().AddSound("Data/Resources/DeathSound.wav");
	ServiceLocator::GetSoundSystem().AddSound("Data/Resources/piano2.wav");
}

void dae::DiggerSceneManager::InitInput()
{
	//controls
	InputManager::GetInstance().BindKeyboardCommand(SDL_SCANCODE_F1,
		InputManager::TriggerType::IsDownThisFrame,
		std::make_unique<SkipToNextLevelCommand>(this));

	InputManager::GetInstance().BindKeyboardCommand(SDL_SCANCODE_F2
		, InputManager::TriggerType::IsDownThisFrame
		, std::make_unique<MuteSoundCommand>());
}

void dae::DiggerSceneManager::Notify(GameEvent event, GameObject*  )
{
	m_currentGameState->ProccessNotificationsScenes(event, this);
}

void dae::DiggerSceneManager::SetState(std::unique_ptr<GameState> newState)
{
	if(m_currentGameState)
	m_currentGameState->OnExit(this);

	m_currentGameState = std::move(newState);
	m_currentGameState->OnEnter(this);

	LoadScreen();
}
