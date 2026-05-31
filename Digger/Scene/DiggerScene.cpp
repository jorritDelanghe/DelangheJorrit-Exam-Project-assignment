#include "DiggerScene.h"
#include "SceneManager.h"
#include <memory>

#include "RenderComponent.h"

#include <SDL3/SDL.h> //needs to be above inputmanager otherwise it doesnt know it
#include "InputManager.h"
#include "Player/MoveDiggerCommand.h"


#include "Grid/GridComponent.h"
#include "Goldbag/GoldBagComponent.h"
#include "GameObject.h"

#include "LivesDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "ResourceManager.h"
#include "PointsComponent.h"
#include "Player/HealthComponent.h"

//sound
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

//text 
#include "TextComponent.h"
#include "Font.h"

//enemy
#include "GameTime.h"
#include "Enemy/EnemyComponent.h"
#include "Enemy/EnemyUtilityAI.h"
#include "Enemy/EnemyWanderingState.h"
#include "Enemy/EnemyChasingState.h"
#include "Enemy/EnemyDiggingState.h"
#include "Collision/RectColliderComponent.h"
#include "Collision/CollisionSystem.h"
#include "Collision/CollisionUpdaterComponent.h"
namespace dae
{
	DiggerScene::DiggerScene()
	{
	}
	void DiggerScene::LoadScene()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene();
		auto grid = InitGrid(scene, "Data/Resources/Level01.txt");
		auto player = InitPlayer(scene, "digger2.png");

		InitSound();
		SpawnGameResources(scene, grid, player->GetComponent<PointsComponent>(), player);
		SetupInputControls(grid, player, player->GetComponent<PointsComponent>()
			, player->GetComponent<HealthComponent>());
		InitUI(scene, player->GetComponent<PointsComponent>(), player->GetComponent<HealthComponent>());
	}

	GridComponent* DiggerScene::InitGrid(Scene& scene, const std::string& levelFile)
	{
		auto gridObject = std::make_unique<GameObject>(); //first create the gameobject
		gridObject->AddComponent<GridComponent>(levelFile); //then add the grid component to it
		auto* rawPtrGrid{ gridObject->GetComponent<GridComponent>() };
		scene.Add(std::move(gridObject)); //then add the gameobject to the scene	

		return rawPtrGrid;
	}

	GameObject* DiggerScene::InitPlayer(Scene& scene, const std::string& filepath)
	{
		constexpr int numLives{ 3 };
		auto diggerPlayer{ std::make_unique<GameObject>() };
		auto* rawDiggerPtr{ diggerPlayer.get() };
		auto* playerImage = diggerPlayer->AddComponent<RenderComponent>(filepath);
		diggerPlayer->AddComponent<RectColliderComponent>(Size
			{
				playerImage->GetSizeImage().width
				, playerImage->GetSizeImage().height
			}, CollisionTag::Player);
		diggerPlayer->AddComponent<PointsComponent>();
		diggerPlayer->AddComponent<HealthComponent>(numLives);
		diggerPlayer->SetLocalPosition({ 100.f,100.f,0.f });

		scene.Add(std::move(diggerPlayer));
		return rawDiggerPtr;
	}

	void DiggerScene::InitSound() const
	{
		ServiceLocator::RegisterSounSystem(std::make_unique<SDLSoundSystem>());
		ServiceLocator::GetSoundSystem().AddSound("Data/Resources/DeathSound.wav");
		ServiceLocator::GetSoundSystem().AddSound("Data/Resources/piano2.wav");
	}

	void DiggerScene::SpawnGameResources(Scene& scene, GridComponent* rawPtrGrid
		, PointsComponent* points, GameObject* diggerRawPtr)
	{
		const Grid& grid{ rawPtrGrid->GetGrid() };
		for (int r{}; r < grid.GetRows();++r)
		{
			for (int c{}; c < grid.GetCols();++c)
			{
				const glm::vec3 pos{ rawPtrGrid->ColToWorld(c), rawPtrGrid->RowToWorld(r), 0.f };
				switch (grid.GetTileType(c, r))
				{
					case TileType::Emerald:
						SpawnEmeralds(scene, rawPtrGrid, pos);
						break;
					case TileType::GoldBag:
						SpawnGoldBags(scene, rawPtrGrid, pos);
						break;
						case TileType::EnemySpawn:
						SpawnEnemies(scene, rawPtrGrid, diggerRawPtr, points, pos);
						rawPtrGrid->DiggedTile(c, r); //dig out the enemy spawn tile so it doesnt block movement
						break;
				}
			}
		}

		//update collsions
		auto collisionUpdater = std::make_unique<GameObject>();
		collisionUpdater->AddComponent<CollisionUpdaterComponent>();
		scene.Add(std::move(collisionUpdater));
	}

	void DiggerScene::SpawnGoldBags(Scene& scene, GridComponent* grid, const glm::vec3& pos)
	{
		auto goldBagObj = std::make_unique<GameObject>();
		goldBagObj->AddComponent<GoldBagComponent>(grid);
		goldBagObj->AddComponent<RenderComponent>("Resources/goldBagSingle.png");

		goldBagObj->SetLocalPosition(pos);
		scene.Add(std::move(goldBagObj));
	}

	void DiggerScene::SpawnEmeralds(Scene& scene, GridComponent* rawPtrGrid, const glm::vec3& pos)
	{
		auto EmeraldObj = std::make_unique<GameObject>();
		EmeraldObj->AddComponent<GoldBagComponent>(rawPtrGrid);
		EmeraldObj->AddComponent<RenderComponent>("Resources/Emerald.png");

		EmeraldObj->SetLocalPosition(pos);
		scene.Add(std::move(EmeraldObj));
	}

	void DiggerScene::SpawnEnemies(Scene& scene, GridComponent* rawPtrGrid
		, GameObject* player, PointsComponent* points, const glm::vec3& pos)
	{
		//actions
		constexpr float speed = 100.f;
		constexpr float chasingRadius = 150.f;
		constexpr float maxChaseRange = 300.f;

		//spawn enemy
		auto enemyObj = std::make_unique<GameObject>();
		auto* enemy = enemyObj->AddComponent<EnemyComponent>(rawPtrGrid, player);
		auto* enemyImage = enemyObj->AddComponent<RenderComponent>("Resources/SoloNobbin.png");
		enemyObj->AddComponent<RectColliderComponent>(Size
			{
				enemyImage->GetSizeImage().width
				, enemyImage->GetSizeImage().height
			}, CollisionTag::Enemy);
		enemyObj->SetLocalPosition(pos);

		//create utilityAI and register actions
		auto* enemyUtilityAI = enemyObj->AddComponent<EnemyUtilityAI>(enemy, rawPtrGrid, player, points);
		RegisterAIUtilityActions(enemyUtilityAI, speed, chasingRadius, maxChaseRange, points);
		
		scene.Add(std::move(enemyObj));
	}

	void DiggerScene::RegisterAIUtilityActions(dae::EnemyUtilityAI* utilityAI
		, float speed, float chasingRadius, float /*maxChaseRange*/, PointsComponent*)
	{
		utilityAI->RegisterNewAction("Chasing",
			[chasingRadius](const EnemyUtilityAI::GameStats& gameStats)
			{
				//closer hte higher score
				const float score{ 1.f - EnemyUtilityAI::GetLinearCurve(gameStats.distancePlayer, chasingRadius) };
				return EnemyUtilityAI::GetScoringQuadraticCurve(score, 1.f); //more decisive avction
			}
			, [speed]()
			{
				return new EnemyChasingState(speed);
			});

		utilityAI->RegisterNewAction("Digging",
			[](const EnemyUtilityAI::GameStats& gameStats)
			{
				if (gameStats.isOnTunnel) return 0.1f; // discourage digging on tunnels
				float farness = EnemyUtilityAI::GetLinearCurve(gameStats.distancePlayer, 500.f);
				return EnemyUtilityAI::GetScoringQuadraticCurve(farness, 1.f);
			}
			, [speed]()
			{
				return new EnemyDiggingState(speed, "Resources/SoloNobbin.png", "Resources/SoloHobbin.png");
			});

		utilityAI->RegisterNewAction("Wandering",
			[chasingRadius](const EnemyUtilityAI::GameStats& gameStats)
			{
				const float distanceToWander{ EnemyUtilityAI::GetLinearCurve(gameStats.distancePlayer,chasingRadius) };

				if (gameStats.collectedPoints > 100) //if player has more than 100 points, enemies will wander less
				{
					const float negativeScore{ -0.2f }; //wander lesss
					return EnemyUtilityAI::GetScoringQuadraticCurve(distanceToWander + negativeScore, 1.f);
				}
				return EnemyUtilityAI::GetScoringQuadraticCurve(distanceToWander, 1.f);
			}
			, [speed]()
			{

				return new EnemyWanderingState(speed);
			});
	}

	void DiggerScene::InitUI(Scene& scene, PointsComponent* points, HealthComponent* health)
	{
		// lives display object
		auto font = dae::ResourceManager::GetInstance().LoadFont("Resources/GameFont.ttf", 36);
		auto livesDisplayObj = std::make_unique<GameObject>();
		auto* livesDisplay = livesDisplayObj->AddComponent<LivesDisplayComponent>("digger2.png", 40.f, 5.f, 3);
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
		CollisionSystem::GetInstance().OnHitSubject().AddObservers(health);

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

	}

	void DiggerScene::SetupInputControls(GridComponent* rawPtrGrid, GameObject* diggerPlayerRawPtr
		, PointsComponent* points, HealthComponent* )
	{
		const SoundID digSound{ ServiceLocator::GetSoundSystem().AddSound("Data/Resources/DeathSound.wav") };
		const SoundID gemSound{ ServiceLocator::GetSoundSystem().AddSound("Data/Resources/piano2.wav") };
		// controls keyboard
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
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,-1.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		input.BindKeyboardCommand(SDL_SCANCODE_A
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ -1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		input.BindKeyboardCommand(SDL_SCANCODE_S
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 0.f,1.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		input.BindKeyboardCommand(SDL_SCANCODE_D
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		//arrows

		input.BindKeyboardCommand(SDL_SCANCODE_UP
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,-1.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		input.BindKeyboardCommand(SDL_SCANCODE_LEFT
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ -1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		input.BindKeyboardCommand(SDL_SCANCODE_DOWN
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 0.f,1.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		input.BindKeyboardCommand(SDL_SCANCODE_RIGHT
			, InputManager::TriggerType::Isdown
			, std::make_unique<MoveDiggerCommand>
			(diggerPlayerRawPtr, speed, glm::vec3{ 1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		//gamepad
		input.BindControllerCommand(dae::GamepadButton::DpadUp,
			InputManager::TriggerType::Isdown,
			std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,-1.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		input.BindControllerCommand(dae::GamepadButton::DpadDown,
			InputManager::TriggerType::Isdown,
			std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 0.f,1.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		input.BindControllerCommand(dae::GamepadButton::DpadLeft,
			InputManager::TriggerType::Isdown,
			std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ -1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points));

		input.BindControllerCommand(dae::GamepadButton::DpadRight,
			InputManager::TriggerType::Isdown,
			std::make_unique<MoveDiggerCommand>(
				diggerPlayerRawPtr, speed, glm::vec3{ 1.f,0.f,0.f }, rawPtrGrid, digSound, gemSound, points));

	}


}