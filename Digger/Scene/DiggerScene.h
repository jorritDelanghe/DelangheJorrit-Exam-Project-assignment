#pragma once
#include "BaseScene.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>
namespace dae
{
	class GridComponent;
	class Scene;
	class GameObject;
	class PointsComponent;
	class HealthComponent;
	class GoldBagComponent;
	class EnemyUtilityAI;
	class DiggerScene : public BaseScene
	{
	public:
		DiggerScene();
		virtual ~DiggerScene() override = default;

		DiggerScene(const DiggerScene& other) = delete;
		DiggerScene( DiggerScene&& other) = delete;
		DiggerScene& operator=(const DiggerScene& other) = delete;
		DiggerScene& operator=( DiggerScene&& other) = delete;

		virtual void LoadScene() override;
	private:
		GridComponent* InitGrid(Scene& scene, const std::string& levelFile);
		GameObject* InitPlayer(Scene& scene,const std::string& filename);
		void InitSound() const;
		void SpawnGameResources(Scene& scene, GridComponent* rawPtrGrid
			, PointsComponent* points, GameObject* diggerRawPtr);

		//spawn  game entities
		void SpawnGoldBags(Scene& scene, GridComponent* grid, const glm::vec3& pos);
		void SpawnEmeralds(Scene& scene, GridComponent* rawPtrGrid, const glm::vec3& pos);
		void SpawnEnemies(Scene& scene, GridComponent* rawPtrGrid, GameObject* player
			, PointsComponent* points, const glm::vec3& pos);
		
		void RegisterAIUtilityActions(dae::EnemyUtilityAI* utilityAI,float speed, float chasingRadius, float maxChaseRange, PointsComponent* points);
		
		void InitUI(Scene& scene, PointsComponent* points, HealthComponent* health);
		void SetupInputControls(GridComponent* grid, GameObject* player
			, PointsComponent* points, HealthComponent* health);
	};
}
