#pragma once

enum EntityType : int
{
	ET_NONE		= 0,
	ET_PLAYER	= 1 << 0,
	ET_TILE		= 1 << 1,
	ET_ENEMY	= 1 << 2, 
	ET_PICKUP	= 1 << 3,
	ET_BULLET	= 1 << 4
};

enum TileType : int
{
	TT_NONE		= 0,
	TT_GROUND,
	TT_WALL,
	TT_WATER
};

enum class State
{
	Start,
	RunGame,
	End
};

enum class PickupType
{
	Ammo,
	Health
};