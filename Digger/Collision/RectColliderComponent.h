#pragma once
#include "Component.h"
#include "DataTypes.h"
#include "Subject.h"
#include <memory>
namespace dae
{
	enum class CollisionTag
	{
		Player
		, Enemy
		, GoldBag
		, Border
		, Emerald
		, GoldNugget
		, FallingGoldBag
	};
	class GameObject;
	class RectColliderComponent final : public Component
	{
	public:
		explicit RectColliderComponent(GameObject* pOwner,const Size& size, CollisionTag tag);

		virtual ~RectColliderComponent() override;
		RectColliderComponent(const RectColliderComponent& other) = delete;
		RectColliderComponent(RectColliderComponent&& other) = delete;
		RectColliderComponent& operator=(const RectColliderComponent& other) = delete;
		RectColliderComponent& operator=(RectColliderComponent&& other) = delete;

		virtual void Update(float deltaTime) override; 
		virtual void Render()const override; //debug purposes
		const Rect& GetBoundingBoxInWorld() const;
		CollisionTag GetTag()const { return m_tag; }

	private:
		Rect m_boundingBox{};
		CollisionTag m_tag{};
	};

}