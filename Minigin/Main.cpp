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
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	//background
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent(std::make_unique<dae::TransformComponent>());
	go->AddComponent(std::make_unique<dae::RenderComponent>("background.png"));
	scene.Add(std::move(go));

	//logo
	go = std::make_unique<dae::GameObject>();
	go->AddComponent(std::make_unique<dae::RenderComponent>("logo.png"));
	auto transform = std::make_unique<dae::TransformComponent>();
	transform->SetPosition(100, 100);
	go->AddComponent(std::move(transform));
	scene.Add(std::move(go));

	//fps counter
	go = std::make_unique<dae::GameObject>();
	transform = std::make_unique<dae::TransformComponent>();
	transform->SetPosition(10, 10);
	go->AddComponent(std::move(transform));
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	// Explicitly construct the color to avoid passing a braced-init-list into make_unique
	SDL_Color white{ 255, 255, 255, 255 };
	auto textComp = std::make_unique<dae::TextComponent>(font, white);  // White
	textComp->SetText("FPS: 0");
	go->AddComponent(std::move(textComp));

	// 2. Add FPSComponent (updates the text)
	go->AddComponent(std::make_unique<dae::FPSComponent>());
	scene.Add(std::move(go));

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
