#pragma once
namespace dae
{
	enum class GameEvent
	{
		//pickup
		PlayerPickedUp,

		//die
		PlayerDied,
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