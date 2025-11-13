#include "Tile.h"

Tile::Tile(TileType tileType, X::Math::Vector2& position)
	: mTileType(tileType)
	, mPosition(position)
	, mImageId(0)
{
}

Tile::~Tile()
{
}

void Tile::Load()
{
	switch (mTileType)
	{
	case Grass: mImageId = X::LoadTexture("grass.png"); break;
	case GrassFlower: mImageId = X::LoadTexture("flower.png"); break;
	case Dirt: mImageId = X::LoadTexture("grass_2.png"); break;
	case DirtFlower: mImageId = X::LoadTexture("flower_2.png"); break;
	case GrassTree1: mImageId = X::LoadTexture("tree0.png"); break;
	case GrassTree2: mImageId = X::LoadTexture("tree1.png"); break;
	case GrassTree3: mImageId = X::LoadTexture("tree2.png"); break;
	case GrassTree4: mImageId = X::LoadTexture("tree3.png"); break;
	case DirtTree1: mImageId = X::LoadTexture("tree0_2.png"); break;
	case DirtTree2: mImageId = X::LoadTexture("tree1_2.png"); break;
	case DirtTree3: mImageId = X::LoadTexture("tree2_2.png"); break;
	case DirtTree4: mImageId = X::LoadTexture("tree3_2.png"); break;
	default:
		break;
	}
}
void Tile::Update(float deltaTime)
{

}
void Tile::Render()
{
	X::DrawSprite(mImageId, mPosition, X::Pivot::TopLeft);
}
void Tile::Unload()
{

}
