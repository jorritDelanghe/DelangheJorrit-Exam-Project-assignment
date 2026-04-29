#include "DiggerScene.h"
#include "SceneManager.h"
#include <memory>

#include "RenderComponent.h"

#include <SDL3/SDL.h> //needs to be above inputmanager otherwise it doesnt know it
#include "InputManager.h"
#include "MoveDiggerCommand.h"


#include "GridComponent.h"
#include "GameObject.h"

#include "LivesDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "ResourceManager.h"
#include "PointsComponent.h"
#include "HealthComponent.h"

//sound
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
namespace dae
{
	void diggerScene::loadScene()
	{
		//scene
		auto& scene = dae::SceneManager::GetInstance().CreateScene();

		auto gridObject = std::make_unique<GameObject>(); //first create the gameobject
		gridObject->AddComponent<GridComponent>("Data/Resources/Level01.txt"); //then add the grid component to it
		gridObject->SetLocalPosition({ 0.f,40.f,0.f });
		auto* rawPtrGrid{ gridObject->GetComponent<GridComponent>()};
		scene.Add(std::move(gridObject)); //then add the gameobject to the scene	

		//sound
		ServiceLocator::RegisterSounSystem(std::make_unique<SDLSoundSystem>());
		SoundID digSound{ ServiceLocator::GetSoundSystem().AddSound("Resources/DeathSound.wav") };

		//player
		constexpr int numLives{ 3 };
		auto diggerPlayer{ std::make_unique<GameObject>() };
		diggerPlayer->AddComponent<RenderComponent>("digger2.png");
		auto* points = diggerPlayer->AddComponent<PointsComponent>();
		auto* health = diggerPlayer->AddComponent<HealthComponent>(numLives);
		diggerPlayer->SetLocalPosition({ 100.f,100.f,0.f });

		auto* diggerPlayerRawPtr{ diggerPlayer.get() };
		scene.Add(std::move(diggerPlayer));

		// lives display object
		auto font = dae::ResourceManager::GetInstance().LoadFont("Resources/GameFont.ttf", 36);
		auto livesDisplayObj = std::make_unique<GameObject>();
		auto* livesDisplay = livesDisplayObj->AddComponent<LivesDisplayComponent>("digger2.png",40.f,5.f,3);
		livesDisplayObj->SetLocalPosition({ 110.f, 0.f, 0.f });
		scene.Add(std::move(livesDisplayObj));
	
		//points display
		constexpr SDL_Color green{ 0,255,0,255 };
		auto pointsDisplayObj = std::make_unique<GameObject>();
		auto* pointsDisplay = pointsDisplayObj->AddComponent<PointsDisplayComponent>(font, green);
		pointsDisplayObj->SetLocalPosition({ 10.f, 0.f, 0.f });
		scene.Add(std::move(pointsDisplayObj));
	
		//observers
		health->OnDied().AddObservers(livesDisplay);
		points->OnPointsChanged().AddObservers(pointsDisplay);
	

		//controls keyboard
		auto& input = InputManager::GetInstance();
		constexpr float speed{ 100.f };


		input.BindKeyboardCommand(SDL_SCANCODE_W
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,-1.f,0.f }, rawPtrGrid, digSound));

		input.BindKeyboardCommand(SDL_SCANCODE_A
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ -1.f,0.f,0.f }, rawPtrGrid, digSound));

		input.BindKeyboardCommand(SDL_SCANCODE_S
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 0.f,1.f,0.f }, rawPtrGrid, digSound));

		input.BindKeyboardCommand(SDL_SCANCODE_D
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 1.f,0.f,0.f }, rawPtrGrid, digSound));

		//arrows

		input.BindKeyboardCommand(SDL_SCANCODE_UP
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,-1.f,0.f }, rawPtrGrid, digSound));

		input.BindKeyboardCommand(SDL_SCANCODE_LEFT
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ -1.f,0.f,0.f }, rawPtrGrid, digSound));

		input.BindKeyboardCommand(SDL_SCANCODE_DOWN
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 0.f,1.f,0.f }, rawPtrGrid, digSound));

		input.BindKeyboardCommand(SDL_SCANCODE_RIGHT
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 1.f,0.f,0.f }, rawPtrGrid, digSound));
		
	}

}