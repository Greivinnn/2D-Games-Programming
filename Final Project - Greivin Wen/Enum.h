#pragma once

enum EntityType : int
{
	ET_NONE = 0,
	ET_PLAYER = 1 << 0,
	ET_TILE = 1 << 1,
	ET_ENEMY = 1 << 2,
	ET_PICKUP = 1 << 3,
	ET_PLAYER_PROJECTILE = 1 << 4,
	ET_ENEMY_PROJECTILE = 1 << 5
};

enum TileType : int
{
	TT_NONE		= 0,
	TT_GROUND,
	TT_WALL,
	TT_WATER
};

enum MovementState : int
{
	MS_NONE = 0,
	MS_IDLE,
	MS_WALK,
	MS_JUMP,
	MS_FALL
};