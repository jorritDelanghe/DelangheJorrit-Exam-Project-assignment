#include "DiggerScene.h"
#include "SceneManager.h"
#include <memory>

#include "GridComponent.h"
#include "GameObject.h"
namespace dae
{
	void diggerScene::loadScene()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene();

		auto gridObject = std::make_unique<GameObject>(); //first create the gameobject
		gridObject->AddComponent<GridComponent>("Data/Resources/Level01.txt"); //then add the grid component to it
		scene.Add(std::move(gridObject)); //then add the gameobject to the scene	

	}

}