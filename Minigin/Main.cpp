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
	auto centerWidget = std::make_unique<GameObject>();
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
	scene.Add(std::move(childCharacter2));

	//add IMGUI Trash The Cash
	auto cacheTestObj = std::make_unique<GameObject>();
	cacheTestObj->AddComponent<CacheTestComponent>();
	scene.Add(std::move(cacheTestObj));

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
