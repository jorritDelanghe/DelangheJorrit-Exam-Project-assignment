#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "CacheTestComponent.h"
#include "Scene.h"
#include "GameObjectCommand.h"
#include "InputManager.h"
#include "HealthComponent.h"
#include "LivesDisplayComponent.h"
#include "PointsComponent.h"
#include "PointsDisplayComponent.h"
#include <filesystem>
namespace fs = std::filesystem;
using namespace dae;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	//background
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("background.png");
	scene.Add(std::move(go));

	//logo
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("logo.png");
	go->SetLocalPosition({ 400.f,240.f,0.f });
	scene.Add(std::move(go));

	//fps counter
	go = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	// Explicitly construct the color to avoid passing a braced-init-list into make_unique
	SDL_Color white{ 255, 255, 255, 255 };
	auto textComp = go->AddComponent<dae::TextComponent>(font, white);  // White
	textComp->SetText("FPS: 0");

	//Add FPSComponent (updates the text)
	go->AddComponent<FPSComponent>();
	scene.Add(std::move(go));

	//rotating diggers
	/*auto centerWidget = std::make_unique<GameObject>();
	centerWidget->SetLocalPosition({ 500.f, 500.f, 0.f });

	auto childCharacter1 = std::make_unique<GameObject>();
	auto childCharacter2 = std::make_unique<GameObject>();

	childCharacter1->SetParent(centerWidget.get());
	childCharacter1->AddComponent<RenderComponent>("digger2.png");
	childCharacter1->AddComponent<RotatorComponent>(10.f, 10.f);

	childCharacter2->SetParent(childCharacter1.get());
	childCharacter2->AddComponent<RenderComponent>("digger2.png");
	childCharacter2->AddComponent<RotatorComponent>(-5.f, 50.f);

	scene.Add(std::move(centerWidget));
	scene.Add(std::move(childCharacter1));
	scene.Add(std::move(childCharacter2));*/

	//add IMGUI Trash The Cash
	/*auto cacheTestObj = std::make_unique<GameObject>();
	cacheTestObj->AddComponent<CacheTestComponent>();
	scene.Add(std::move(cacheTestObj));*/

	// instruction text player 1 (controller)
	auto instructionP1 = std::make_unique<GameObject>();
	instructionP1->SetLocalPosition({ 10.f, 30.f, 0.f });
	auto* textP1 = instructionP1->AddComponent<TextComponent>(font, white);
	textP1->SetText("Use the D-Pad to move player 1, SPACE to die, E to gain points");
	scene.Add(std::move(instructionP1));

	// instruction text player 2 (keyboard)
	auto instructionP2 = std::make_unique<GameObject>();
	instructionP2->SetLocalPosition({ 10.f, 60.f, 0.f });
	auto* textP2 = instructionP2->AddComponent<TextComponent>(font, white);
	textP2->SetText("Use WASD to move player 2, Q to die, Z to gain points");
	scene.Add(std::move(instructionP2));

	//add move player 2
	constexpr float speed{ 100.f };
	constexpr float doubleSpeed{ speed * 2.f };
	auto controllerPlayer = std::make_unique<GameObject>();
	controllerPlayer->SetLocalPosition({ 300.f,300.f,0.f });
	GameObject* pPlayer = controllerPlayer.get();
	controllerPlayer->AddComponent<RenderComponent>("digger2.png");
	auto* health = controllerPlayer->AddComponent<HealthComponent>(3);
	auto* points = controllerPlayer->AddComponent<PointsComponent>();
	scene.Add(std::move(controllerPlayer));

	// lives display object
	auto livesDisplayObj = std::make_unique<GameObject>();
	auto* livesDisplay = livesDisplayObj->AddComponent<LivesDisplayComponent>(font, SDL_Color{ 255,255,255,255 },3);
	livesDisplayObj->SetLocalPosition({ 10.f, 100.f, 0.f });
	scene.Add(std::move(livesDisplayObj));

	//points display
	auto pointsDisplayObj = std::make_unique<GameObject>();
	auto* pointsDisplay = pointsDisplayObj->AddComponent<PointsDisplayComponent>(font, SDL_Color{ 255,255,255,255 });
	pointsDisplayObj->SetLocalPosition({ 10.f, 130.f, 0.f });
	scene.Add(std::move(pointsDisplayObj));

	//observers
	health->OnDied().AddObservers(livesDisplay);
	points->OnPointsChanged().AddObservers(pointsDisplay);

	auto& input = InputManager::GetInstance();
	//dead bind input
	input.BindKeyboardCommand(SDL_SCANCODE_SPACE, InputManager::TriggerType::IsDownThisFrame, std::make_unique<DieCommand>(pPlayer));
	input.BindKeyboardCommand(SDL_SCANCODE_E, InputManager::TriggerType::IsDownThisFrame,
		std::make_unique<GainPointsCommand>(pPlayer, 10));

	input.BindControllerCommand(dae::GamepadButton::DpadUp, InputManager::TriggerType::Isdown,
		std::make_unique<MoveGameObjectCommand>
	(pPlayer, doubleSpeed, glm::vec3{ 0.f,-1.f,0.f }));

	input.BindControllerCommand(dae::GamepadButton::DpadDown, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>
		(pPlayer, doubleSpeed, glm::vec3{ 0.f,1.f,0.f }));

	input.BindControllerCommand(dae::GamepadButton::DpadRight, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>
		(pPlayer, doubleSpeed, glm::vec3{ 1.f,0.f,0.f }));

	input.BindControllerCommand(dae::GamepadButton::DpadLeft, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>
		(pPlayer, doubleSpeed, glm::vec3{ -1.f,0.f,0.f }));

	//add move player1
	auto keyBoardPlayer = std::make_unique<GameObject>();
	keyBoardPlayer->SetLocalPosition({ 300.f,350.f,0.f });
	GameObject* pKeyPlayer = keyBoardPlayer.get();
	keyBoardPlayer->AddComponent<RenderComponent>("digger2.png");
	auto* health1 = keyBoardPlayer->AddComponent<HealthComponent>(3);
	auto* points1 = keyBoardPlayer->AddComponent<PointsComponent>();
	scene.Add(std::move(keyBoardPlayer));

	// lives display object
	auto livesDisplayObjPlayer1 = std::make_unique<GameObject>();
	auto* livesDisplayPlayer1 = livesDisplayObjPlayer1->AddComponent<LivesDisplayComponent>(font, SDL_Color{ 255,255,255,255 }, 3);
	livesDisplayObjPlayer1->SetLocalPosition({ 10.f, 170.f, 0.f });
	scene.Add(std::move(livesDisplayObjPlayer1));

	//points display
	auto pointsDisplayObjPlayer1 = std::make_unique<GameObject>();
	auto* pointsDisplayPlayer1 = pointsDisplayObjPlayer1->AddComponent<PointsDisplayComponent>(font, SDL_Color{ 255,255,255,255 });
	pointsDisplayObjPlayer1->SetLocalPosition({ 10.f, 200.f, 0.f });
	scene.Add(std::move(pointsDisplayObjPlayer1));

	//observers
	health1->OnDied().AddObservers(livesDisplayPlayer1);
	points1->OnPointsChanged().AddObservers(pointsDisplayPlayer1);


	//dead bind input
	input.BindKeyboardCommand(SDL_SCANCODE_Q, InputManager::TriggerType::IsDownThisFrame, std::make_unique<DieCommand>(pKeyPlayer));
	input.BindKeyboardCommand(SDL_SCANCODE_Z, InputManager::TriggerType::IsDownThisFrame, std::make_unique<GainPointsCommand>(pKeyPlayer, 10));
	//wasd
	input.BindKeyboardCommand(SDL_SCANCODE_W, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>(
			pKeyPlayer, speed, glm::vec3{ 0.f,-1.f,0.f }));

	input.BindKeyboardCommand(SDL_SCANCODE_A, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>(
			pKeyPlayer, speed, glm::vec3{ -1.f,0.f,0.f }));

	input.BindKeyboardCommand(SDL_SCANCODE_S, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>(
			pKeyPlayer, speed, glm::vec3{ 0.f,1.f,0.f }));

	input.BindKeyboardCommand(SDL_SCANCODE_D, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>(
			pKeyPlayer, speed, glm::vec3{ 1.f,0.f,0.f }));
	//arrows
	input.BindKeyboardCommand(SDL_SCANCODE_UP, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>(
			pKeyPlayer, speed, glm::vec3{ 0.f,-1.f,0.f }));

	input.BindKeyboardCommand(SDL_SCANCODE_LEFT, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>(
			pKeyPlayer, speed, glm::vec3{ -1.f,0.f,0.f }));

	input.BindKeyboardCommand(SDL_SCANCODE_DOWN, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>(
			pKeyPlayer, speed, glm::vec3{ 0.f,1.f,0.f }));

	input.BindKeyboardCommand(SDL_SCANCODE_RIGHT, InputManager::TriggerType::Isdown
		, std::make_unique<MoveGameObjectCommand>(
			pKeyPlayer, speed, glm::vec3{ 1.f,0.f,0.f }));


	/*auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<dae::TextObject>("Programming 4 Assignment", font);
	to->SetColor({ 255, 255, 0, 255 });
	to->SetPosition(292, 20);
	scene.Add(std::move(to));*/
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
