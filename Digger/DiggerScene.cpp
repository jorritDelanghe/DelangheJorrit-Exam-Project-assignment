#include "DiggerScene.h"
#include "SceneManager.h"
#include <memory>

#include "RenderComponent.h"

#include <SDL3/SDL.h> //needs to be above inputmanager otherwise it doesnt know it
#include "InputManager.h"
#include "GameObjectCommand.h"


#include "GridComponent.h"
#include "GameObject.h"
namespace dae
{
	void diggerScene::loadScene()
	{
		//scene
		auto& scene = dae::SceneManager::GetInstance().CreateScene();

		auto gridObject = std::make_unique<GameObject>(); //first create the gameobject
		gridObject->AddComponent<GridComponent>("Data/Resources/Level01.txt"); //then add the grid component to it
		auto* rawPtrGrid{ gridObject->GetComponent<GridComponent>()};
		scene.Add(std::move(gridObject)); //then add the gameobject to the scene	

		//player
		auto diggerPlayer{ std::make_unique<GameObject>() };
		diggerPlayer->AddComponent<RenderComponent>("digger2.png");
		diggerPlayer->SetLocalPosition({ 100.f,100.f,0.f });

		auto* diggerPlayerRawPtr{ diggerPlayer.get() };
		scene.Add(std::move(diggerPlayer));

		//controls keyboard
		auto& input = InputManager::GetInstance();
		constexpr float speed{ 100.f };


		input.BindKeyboardCommand(SDL_SCANCODE_W
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveGameObjectCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,-1.f,0.f }, rawPtrGrid));

		input.BindKeyboardCommand(SDL_SCANCODE_A
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveGameObjectCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ -1.f,0.f,0.f }, rawPtrGrid));

		input.BindKeyboardCommand(SDL_SCANCODE_S
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveGameObjectCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 0.f,1.f,0.f }, rawPtrGrid));

		input.BindKeyboardCommand(SDL_SCANCODE_D
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveGameObjectCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 1.f,0.f,0.f }, rawPtrGrid));
		
	}

}