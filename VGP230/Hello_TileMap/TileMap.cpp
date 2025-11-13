#include "TileMap.h"

TileMap::TileMap()
	: mTileMap(NULL)
{

}
TileMap::~TileMap()
{
	XASSERT(mTileMap.empty(), "TileMap: not unloaded");
}

void TileMap::Load()
{

}
void TileMap::Update(float deltaTime)
{
	for (Tile* tile : mTileMap)
	{
		tile->Update(deltaTime);
	}
}
void TileMap::Render()
{
	for (Tile* tile : mTileMap)
	{
		tile->Render();
	}
}
void TileMap::Unload()
{
	for (Tile* tile : mTileMap)
	{
		tile->Unload();
		delete tile;
		tile = nullptr;
	}
	mTileMap.clear();
}

void TileMap::LoadMap(const std::vector<int>& tiles, int columns, float size)
{
	XASSERT(tiles.size() % columns == 0, "TileMap: tiles dont line up with columns");
	X::Math::Vector2 position = X::Math::Vector2::Zero();
	for (int i = 0; i < tiles.size(); ++i)
	{
		if (i > 0 && i % columns == 0)
		{
			position.y += size;
			position.x = 0.0f;
		}
		Tile* newTile = new Tile((TileType)tiles[i], position);
		newTile->Load();
		mTileMap.push_back(newTile);
		position.x += size;
	}

}
