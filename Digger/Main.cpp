
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include <filesystem>

//digger scene
#include "Minigin.h"
#include "DiggerScene.h"

namespace fs = std::filesystem;
using namespace dae;

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(diggerScene::loadScene);
    return 0;
}
