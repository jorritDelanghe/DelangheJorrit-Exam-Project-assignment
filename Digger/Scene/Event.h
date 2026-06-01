#pragma once
namespace dae
{
	enum class GameEvent
	{
		PlayerDied,
		PlayerPickedUp,
		EnemyDied,

		CollisionWall,
		CollisionEnemy,
		CollisionGoldBag,
		CollisionDirtWall,
		CollisionEmerald,
		CollisionGoldNugget,
		CollisionFallingBag,
		CollisionPlayer
	};
}