#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float fixedDeltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(fixedDeltaTime);
	}
}

void dae::SceneManager::Render(float extraPolation)
{
	for (const auto& scene : m_scenes)
	{
		scene->Render(extraPolation);
	}
}

dae::Scene& dae::SceneManager::CreateScene()
{
	m_scenes.emplace_back(new Scene());
	return *m_scenes.back();
}
