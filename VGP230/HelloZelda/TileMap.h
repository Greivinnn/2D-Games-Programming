#pragma once
#include "Tile.h"

class TileMap : public Entity
{
public:
	~TileMap() override;

	static TileMap* Get();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

private:
	TileMap();
	static TileMap* mInstance;

	void ReloadMap();
	std::vector<Tile*> mTiles;
	int mColumns;
	int mRows;
};