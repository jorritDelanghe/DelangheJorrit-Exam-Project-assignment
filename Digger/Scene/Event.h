#pragma once
namespace dae
{
	enum class GameEvent
	{
		//pickup
		PlayerPickedUp,

		//die
		PlayerDied,
		HealthChanged,
		EnemyDied,

		//collsion
		CollisionWall,
		CollisionEnemy,
		CollisionGoldBag,
		CollisionDirtWall,
		CollisionEmerald,
		CollisionGoldNugget,
		CollisionFallingBag,
		CollisionPlayer,

		//level
		AllEmeraldsCollected
	};
}