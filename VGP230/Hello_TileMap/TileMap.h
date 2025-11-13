#pragma once
#include "Tile.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	void Load();
	void Update(float deltaTime);
	void Render();
	void Unload();

	void LoadMap(const std::vector<int>& tiles, int columns, float size);
private:
	std::vector<Tile*> mTileMap;
};

