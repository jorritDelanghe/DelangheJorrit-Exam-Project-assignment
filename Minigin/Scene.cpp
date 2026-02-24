#include <algorithm>
#include "Scene.h"
#include <assert.h>

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject& object)
{
	m_pendingDeleteObjects.emplace_back(&object);
}

void Scene::RemoveAll()
{
	m_objects.clear();
	m_pendingDeleteObjects.clear();
}

void Scene::Update(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->Update(deltaTime);
	}

	m_objects.erase(
	std::remove_if(
		m_objects.begin()
		, m_objects.end()
		,[&](const auto& obj)
		{ 
			return std::find(
			m_pendingDeleteObjects.begin()
			,m_pendingDeleteObjects.end()
			, obj.get()) != m_pendingDeleteObjects.end(); 
		})
		, m_objects.end()
	);	

	m_pendingDeleteObjects.clear();
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

