#pragma once

#include <XEngine.h>
#include "Enum.h"

class Tile
{
public:
	Tile(TileType tileType, X::Math::Vector2& position);
	~Tile();

	void Load();
	void Update(float deltaTime);
	void Render();
	void Unload();
private:
	TileType mTileType;
	X::Math::Vector2 mPosition;
	X::TextureId mImageId;
};
