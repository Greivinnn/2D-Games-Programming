#include "Tile.h"

Tile::Tile(TileType tileType, const X::Math::Vector2& position)
	: Entity()
	, mTileType(tileType)
	, mPosition(position)
	, mRect(0, 0, 0, 0)
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
	case TT_GROUND: mImageId = X::LoadTexture("grassdirt-big.png"); break;
	case TT_WALL: mImageId = X::LoadTexture("Tree.png"); break;
	case TT_WATER: mImageId = X::LoadTexture("water.png"); break;
	case TT_NONE:
	default:
		XASSERT(false, "Tile: invalide tile type");
	}

	float halfHeight = X::GetSpriteHeight(mImageId) * 0.5f;
	float halfWidth = X::GetSpriteWidth(mImageId) * 0.5f;
	mRect.left = mPosition.x - halfWidth;
	mRect.right = mPosition.x + halfWidth;
	mRect.top = mPosition.y - halfHeight;
	mRect.bottom = mPosition.y + halfHeight;
}
void Tile::Update(float deltaTime)
{

}
void Tile::Render()
{
	X::DrawSprite(mImageId, mPosition);
}
void Tile::Unload()
{

}

const X::Math::Vector2& Tile::GetPosition() const
{
	return mPosition;
}
bool Tile::IsCollidable() const
{
	return mTileType == TT_WALL || mTileType == TT_WATER;
}
bool Tile::HasCollision(const X::Math::Rect& objRect) const
{
	return X::Math::Intersect(mRect, objRect);
}
const X::Math::Rect& Tile::GetRect() const
{
	return mRect;
}