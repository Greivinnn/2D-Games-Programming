#include "Projectile.h"
#include "TileMap.h"
#include "CollisionManager.h"

Projectile::Projectile()
	: Entity()
	, Collidable()
	, mImageId(0)
	, mPosition(0.0f, 0.0f)
	, mProjectileRect(0.0f, 0.0f, 0.0f, 0.0f)
	, mFlip(X::Flip::None)
	, mLifeTime(0.0f)
	, mBulletType(ET_NONE)
	, mDirection(1.0f, 0.0f)
	, mRemoveCollider(false)
{

}
Projectile::~Projectile()
{

}

void Projectile::Load()
{
	mImageId = X::LoadTexture("carrot.png");
	const float halfWidth = X::GetSpriteWidth(mImageId) * 0.5f;
	const float halfHeight = X::GetSpriteHeight(mImageId) * 0.5f;
	mProjectileRect.left = -halfWidth;
	mProjectileRect.right = halfWidth;
	mProjectileRect.top = -halfHeight;
	mProjectileRect.bottom = -halfHeight;
	mLifeTime = 0.0f;
	mBulletType = ET_NONE;
	mFlip = X::Flip::None;
	mRemoveCollider = false;
}
void Projectile::Update(float deltaTime)
{
	if (IsActive())
	{
		const float speed = 200.0f;
		X::Math::Vector2 displacement = mDirection * speed * deltaTime;
		X::Math::Vector2 maxDisplacement = displacement;
		if (TileMap::Get()->HasCollision(GetRect(), maxDisplacement, displacement))
		{
			mLifeTime = 0.0f;
		}
		mPosition += displacement;
		X::Math::Rect currentRect = mProjectileRect;
		currentRect.min += mPosition;
		currentRect.max += mPosition;
		SetRect(currentRect);

		mLifeTime -= deltaTime;
		if (mLifeTime <= 0.0f)
		{
			SetCollisionFilter(ET_NONE);
			mRemoveCollider = true;
		}

	}
	else if (mRemoveCollider)
	{
		CollisionManager::Get()->RemoveCollidable(this);
		mRemoveCollider = false;
	}
}
void Projectile::Render()
{
	if (IsActive())
	{
		X::DrawSprite(mImageId, mPosition, X::Pivot::Center, mFlip);
	}
}
void Projectile::Unload()
{

}

int Projectile::GetType() const
{
	return IsActive() ? mBulletType : 0;
}
void Projectile::OnCollision(Collidable* collidable)
{
	mLifeTime = 0.0f;
	SetCollisionFilter(ET_NONE);
	mRemoveCollider = true;
}
const X::Math::Vector2& Projectile::GetPosition() const
{
	return mPosition;
}

void Projectile::SetActive(const X::Math::Vector2& position, const X::Math::Vector2& direction, float lifeTime)
{
	mPosition = position;
	mDirection = direction;
	mLifeTime = lifeTime;

	X::Math::Rect currentRect = mProjectileRect;
	currentRect.min += position;
	currentRect.max += position;
	SetRect(currentRect);

	CollisionManager::Get()->AddCollidable(this);
	mRemoveCollider = false;
}
void Projectile::SetEntityType(EntityType entityType)
{
	mBulletType = entityType;

	if (entityType == ET_PLAYER_PROJECTILE)
	{
		SetCollisionFilter(ET_ENEMY);
	}
	else if (entityType == ET_ENEMY_PROJECTILE)
	{
		SetCollisionFilter(ET_PLAYER);
	}
}

void Projectile::SetFlip(X::Flip flip)
{

}
bool Projectile::IsActive() const
{
	if (mLifeTime > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}