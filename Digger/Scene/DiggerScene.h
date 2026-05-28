#pragma once
#include "BaseScene.h"
#include <vector>
#include <string>
namespace dae
{
	class GridComponent;
	class Scene;
	class GameObject;
	class PointsComponent;
	class HealthComponent;
	class GoldBagComponent;
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

		void InitUI(Scene& scene, PointsComponent* points, HealthComponent* health);
		void SetupInputControls(GridComponent* grid, GameObject* player
			, PointsComponent* points, HealthComponent* health
			, std::vector<GoldBagComponent*> m_bags);
	};
}
