#include "DiggerScene.h"
#include "SceneManager.h"
#include <memory>

#include "RenderComponent.h"

#include <SDL3/SDL.h> //needs to be above inputmanager otherwise it doesnt know it
#include "InputManager.h"
#include "MoveDiggerCommand.h"


#include "GridComponent.h"
#include "GoldBagComponent.h"
#include "GameObject.h"

#include "LivesDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "ResourceManager.h"
#include "PointsComponent.h"
#include "HealthComponent.h"

//sound
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

//text 
#include "TextComponent.h"
#include "Font.h"

//enemy
#include "GameTime.h"
#include "EnemyComponent.h"
#include "EnemyUtilityAI.h"
#include "EnemyWanderingState.h"
#include "EnemyChasingState.h"
#include "EnemyDiggingState.h"
namespace dae
{
	void diggerScene::loadScene()
	{
		//scene
		auto& scene = dae::SceneManager::GetInstance().CreateScene();

		auto gridObject = std::make_unique<GameObject>(); //first create the gameobject
		gridObject->AddComponent<GridComponent>("Data/Resources/Level01.txt"); //then add the grid component to it
		gridObject->SetLocalPosition({ 0.f,80.f,0.f });
		auto* rawPtrGrid{ gridObject->GetComponent<GridComponent>()};
		scene.Add(std::move(gridObject)); //then add the gameobject to the scene	


		//sound
		ServiceLocator::RegisterSounSystem(std::make_unique<SDLSoundSystem>());
		SoundID digSound{ ServiceLocator::GetSoundSystem().AddSound("Data/Resources/DeathSound.wav") };
		SoundID gemSound{ ServiceLocator::GetSoundSystem().AddSound("Data/Resources/piano2.wav") };

		//player
		constexpr int numLives{ 3 };
		auto diggerPlayer{ std::make_unique<GameObject>() };
		auto* diggerRawPtr = diggerPlayer.get();
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
	
		// add gold bagcomponents
		const Grid& grid{ rawPtrGrid->GetGrid() };
		std::vector<GoldBagComponent*> m_bags;
		std::vector<EnemyComponent*> m_enemies;
		for (int r{}; r < grid.GetRows();++r)
		{
			for (int c{}; c < grid.GetCols();++c)
			{
				if (grid.GetTileType(c, r) == TileType::GoldBag)
				{

					auto goldBagObj = std::make_unique<GameObject>();
					auto* bag = goldBagObj->AddComponent<GoldBagComponent>(rawPtrGrid, points);
					goldBagObj->AddComponent<RenderComponent>("Resources/goldBagSingle.png");

					goldBagObj->SetLocalPosition(
						{
						rawPtrGrid->ColToWorld(c)
						, rawPtrGrid->RowToWorld(r)
						, 0.0f
						});

					m_bags.push_back(bag);
					scene.Add(std::move(goldBagObj));
				
				}
				if (grid.GetTileType(c, r) == TileType::EnemySpawn)
				{

					auto enemyObj = std::make_unique<GameObject>();
					auto* enemy = enemyObj->AddComponent<EnemyComponent>(rawPtrGrid, diggerRawPtr);
					enemyObj->AddComponent<RenderComponent>("Resources/diggerSingle.png");

					//actions
					constexpr float speed = 100.f;
					constexpr float chasingRadius = 150.f;
					constexpr float maxChaseRange = 300.f;

					auto* enemyUtilityAI = enemyObj->AddComponent<EnemyUtilityAI>(enemy, rawPtrGrid, diggerRawPtr, points);
					
					enemyUtilityAI->RegisterNewAction("Chasing",
						[chasingRadius](const EnemyUtilityAI::GameStats& gameStats)
						{
							//closer hte higher score
							const float score{1.f - EnemyUtilityAI::GetLinearCurve(gameStats.distancePlayer, chasingRadius) };
							return EnemyUtilityAI::GetScoringQuadraticCurve(score,1.f); //more decisive avction
						}
						, [speed]()
						{
							return new EnemyChasingState(speed);
						});

					enemyUtilityAI->RegisterNewAction("Digging",
						[](const EnemyUtilityAI::GameStats& gameStats)
						{
							if (gameStats.isOnTunnel) return 0.1f; // discourage digging on tunnels
							float farness = EnemyUtilityAI::GetLinearCurve(gameStats.distancePlayer, 500.f);
							return EnemyUtilityAI::GetScoringQuadraticCurve(farness, 1.f);
						}
						, [speed]()
						{
							return new EnemyDiggingState(speed);
						});

					enemyUtilityAI->RegisterNewAction("Wandering",
						[](const EnemyUtilityAI::GameStats& gameStats)
						{
							const float distanceToWander{ EnemyUtilityAI::GetLinearCurve(gameStats.distancePlayer,maxChaseRange) };

							if (gameStats.collectedPoints > 100) //if player has more than 100 points, enemies will wander less
							{
								const float negativeScore{ -0.2f }; //wander lesss
								return EnemyUtilityAI::GetScoringQuadraticCurve(distanceToWander+negativeScore,1.f);
							}
							return EnemyUtilityAI::GetScoringQuadraticCurve(distanceToWander,1.f);
						}
						, [speed]()
						{
							
							return new EnemyWanderingState(speed);
						});
						

					enemyObj->SetLocalPosition(
						{
						rawPtrGrid->ColToWorld(c)
						, rawPtrGrid->RowToWorld(r)
						, 0.0f
						});

					m_enemies.push_back(enemy);
					scene.Add(std::move(enemyObj));
					rawPtrGrid->DiggedTile(c, r);
				}
			}
		}
		
		
		//instructions
		SDL_Color white{ 255, 255, 255, 255 };
		auto instructionP1 = std::make_unique<GameObject>();
		instructionP1->SetLocalPosition({ 10.f, 450.f, 0.f });
		auto* textP1 = instructionP1->AddComponent<TextComponent>(font, white);
		textP1->SetText("GoldBag moves has Idle, moveState");
		scene.Add(std::move(instructionP1));

		auto instructionP2 = std::make_unique<GameObject>();
		instructionP2->SetLocalPosition({ 10.f, 500.f, 0.f });
		auto* textP2 = instructionP2->AddComponent<TextComponent>(font, white);
		textP2->SetText("Move WASD, arrows, dont press two keys same time");
		scene.Add(std::move(instructionP2));

		//controls keyboard
		auto& input = InputManager::GetInstance();
		constexpr float speed{ 100.f };

		int numJoysticks = 0;
		SDL_JoystickID* joysticks = SDL_GetJoysticks(&numJoysticks);
		SDL_Log("Number of controllers found: %d", numJoysticks);

		for (int i = 0; i < numJoysticks; i++)
		{
			if (SDL_IsGamepad(joysticks[i]))
			{
				SDL_Gamepad* gamepad = SDL_OpenGamepad(joysticks[i]);
				SDL_Log("Controller %d: %s", i, SDL_GetGamepadName(gamepad));
			}
		}
		SDL_free(joysticks);

		input.BindKeyboardCommand(SDL_SCANCODE_W
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,-1.f,0.f }, rawPtrGrid, digSound, gemSound, points,m_bags));

		input.BindKeyboardCommand(SDL_SCANCODE_A
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ -1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points,m_bags));

		input.BindKeyboardCommand(SDL_SCANCODE_S
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 0.f,1.f,0.f }, rawPtrGrid, digSound, gemSound, points,m_bags));

		input.BindKeyboardCommand(SDL_SCANCODE_D
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points,m_bags));

		//arrows

		input.BindKeyboardCommand(SDL_SCANCODE_UP
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,-1.f,0.f }, rawPtrGrid, digSound, gemSound, points,m_bags));

		input.BindKeyboardCommand(SDL_SCANCODE_LEFT
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ -1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points,m_bags));

		input.BindKeyboardCommand(SDL_SCANCODE_DOWN
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 0.f,1.f,0.f }, rawPtrGrid, digSound, gemSound, points,m_bags));

		input.BindKeyboardCommand(SDL_SCANCODE_RIGHT
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points,m_bags));

		//gamepad
		input.BindControllerCommand(dae::GamepadButton::DpadUp,
			InputManager::TriggerType::Isdown,
			std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,-1.f,0.f }, rawPtrGrid, digSound, gemSound, points, m_bags));

		input.BindControllerCommand(dae::GamepadButton::DpadDown,
			InputManager::TriggerType::Isdown,
			std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,1.f,0.f }, rawPtrGrid, digSound, gemSound, points, m_bags));

		input.BindControllerCommand(dae::GamepadButton::DpadLeft,
			InputManager::TriggerType::Isdown,
			std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ -1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points, m_bags));

		input.BindControllerCommand(dae::GamepadButton::DpadRight,
			InputManager::TriggerType::Isdown,
			std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points, m_bags));
		
	}

}