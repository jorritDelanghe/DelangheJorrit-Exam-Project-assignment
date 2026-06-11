#include "SceneManager.h"
#include "InputManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	if (m_pendingClear)
	{
		if (m_scenes.size() > 1)
		{
			m_scenes.erase(m_scenes.begin(), m_scenes.end() - 1);// Clear existing scenes after creating a new one
		}
			m_pendingClear = false;
	}
	for (auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}

	if (m_pendingAction) //avoid crash new level
	{
		auto action = std::move(m_pendingAction);
		m_pendingAction = nullptr;
		action();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene()
{
	m_pendingClear = true;
	m_scenes.emplace_back(new Scene());
	return *m_scenes.back();
}
