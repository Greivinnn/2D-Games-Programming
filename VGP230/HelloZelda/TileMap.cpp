#include "TileMap.h"

TileMap* TileMap::mInstance = nullptr;
TileMap::TileMap()
	: Entity()
	, mColumns(0)
	, mRows(0)
{

}

TileMap::~TileMap()
{

}

TileMap* TileMap::Get()
{
	if (mInstance == nullptr)
	{
		mInstance = new TileMap();
	}
	return mInstance;
}

void TileMap::Load()
{
	ReloadMap();
}
void TileMap::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		ReloadMap();
	}

	for (Tile* tile : mTiles)
	{
		tile->Update(deltaTime);
	}
}
void TileMap::Render()
{
	for (Tile* tile : mTiles)
	{
		tile->Render();
	}

}
void TileMap::Unload()
{
	for (Tile* tile : mTiles)
	{
		tile->Unload();
		delete tile;
		tile = nullptr;
	}
	mTiles.clear();
}	
void TileMap::ReloadMap()
{
	const char fileName[255] = "./Level.lvl";
	std::fstream inputStream;
	inputStream.open(fileName);

	inputStream >> mColumns;
	inputStream >> mRows;

	X::TextureId dummyTile = X::LoadTexture("white.jpg");
	const float tileWidth = X::GetSpriteWidth(dummyTile);
	const float tileHeight = X::GetSpriteHeight(dummyTile);

	Unload();
	X::Math::Vector2 offset = { tileWidth * 0.5f, tileHeight * 0.5f };

	int dataType = 0;
	int tileIndex = 0;
	int x = 0;
	int y = 0;
	while (inputStream >> dataType)
	{
		X::Math::Vector2 position = X::Math::Vector2::Zero();
		TileType tileType = (TileType)dataType;
		x = tileIndex % mColumns;
		y = tileIndex / mColumns;
		position.x = tileWidth * x + offset.x;
		position.y = tileHeight * y + offset.y;

		Tile* newTile = new Tile(tileType, position);
		newTile->Load();
		mTiles.push_back(newTile);
		++tileIndex;
	}
}