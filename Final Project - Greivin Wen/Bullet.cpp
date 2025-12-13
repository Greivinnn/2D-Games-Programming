#include "Bullet.h"
#include "CollisionManager.h"
#include "TileMap.h"

Bullet::Bullet()
	: Entity()
	, Collidable()
	, mImageId(0)
	, mPosition(0.0f)
	, mRotation(0.0f)
	, mLifeTime(0.0f)
	, mBulletType(ET_NONE)
	, mRemoveCollider(false)
{
}

Bullet::~Bullet()
{
}

void Bullet::Load()
{
	mImageId = X::LoadTexture("pixelBullet.png");
}

void Bullet::Update(float deltaTime)
{
	if(mRemoveCollider)
	{
		CollisionManager::Get()->RemoveCollidable(this);
		mRemoveCollider = false;
	}

	if (IsActive())
	{
		mLifeTime -= deltaTime;

		if (!IsActive())
		{
			// Bullet expired, remove from collision
			CollisionManager::Get()->RemoveCollidable(this);
			SetCollisionFilter(ET_NONE);
			return;
		}

		const float speed = 400.0f;
		X::Math::Vector2 direction = X::Math::Vector2::Forward(mRotation) * speed * deltaTime;

		// Check for wall collision
		float halfWidth = X::GetSpriteWidth(mImageId) * 0.5f;
		float halfHeight = X::GetSpriteHeight(mImageId) * 0.5f;
		X::Math::Rect bulletRect;
		bulletRect.left = mPosition.x - halfWidth;
		bulletRect.right = mPosition.x + halfWidth;
		bulletRect.top = mPosition.y - halfHeight;
		bulletRect.bottom = mPosition.y + halfHeight;

		X::Math::Vector2 maxDisplacement = direction;
		X::Math::Vector2 displacement = direction;

		// Check if bullet hits a wall
		if (TileMap::Get()->HasCollision(bulletRect, maxDisplacement, displacement))
		{
			// Hit a wall = deactivate
			mLifeTime = 0.0f;
			CollisionManager::Get()->RemoveCollidable(this);
			SetCollisionFilter(ET_NONE);
			return;
		}

		mPosition += direction;

		// Update collision rect
		bulletRect.left = mPosition.x - halfWidth;
		bulletRect.right = mPosition.x + halfWidth;
		bulletRect.top = mPosition.y - halfHeight;
		bulletRect.bottom = mPosition.y + halfHeight;
		SetRect(bulletRect);

		// in update: the bullets rect calculations are updated every frame based on players position
	}
}

void Bullet::Render()
{
	if (IsActive())
	{
		X::DrawSprite(mImageId, mPosition, mRotation);
	}
}

void Bullet::Unload()
{
}

void Bullet::SetActive(const X::Math::Vector2& pos, float rotation, float lifeTime)
{
	mPosition = pos;
	mRotation = rotation;
	mLifeTime = lifeTime;
	mRemoveCollider = false;

	// Set up collision rect
	float halfWidth = X::GetSpriteWidth(mImageId) * 0.5f;
	float halfHeight = X::GetSpriteHeight(mImageId) * 0.5f;
	X::Math::Rect bulletRect;
	bulletRect.left = mPosition.x - halfWidth;
	bulletRect.right = mPosition.x + halfWidth;
	bulletRect.top = mPosition.y - halfHeight;
	bulletRect.bottom = mPosition.y + halfHeight;
	SetRect(bulletRect);

	// Register with collision manager
	CollisionManager::Get()->AddCollidable(this);
}

void Bullet::SetEntityType(EntityType type)
{
	mBulletType = type;
	if (type == ET_PLAYER)
	{
		SetCollisionFilter(ET_ENEMY);  // Player bullets collide with enemies
	}
	else
	{
		SetCollisionFilter(ET_NONE);	// no ones else shoots bullets beside the player
	}
}

bool Bullet::IsActive() const
{
	return mLifeTime > 0.0f;
}

int Bullet::GetType() const
{
	return IsActive() ? ET_BULLET : ET_NONE;  // Changed: return ET_BULLET when active
}

const X::Math::Vector2& Bullet::GetPosition() const
{
	return mPosition;
}

void Bullet::OnCollision(Collidable* collidable)
{
	if (IsActive())
	{
		mLifeTime = 0.0f;
		mRemoveCollider = true;
		SetCollisionFilter(ET_NONE);
	}
}

void Bullet::SetInactive()
{
	mLifeTime = 0.0f;

	// Only remove from collision if it's currently active
	if (IsActive())
	{
		CollisionManager::Get()->RemoveCollidable(this);
	}

	SetCollisionFilter(ET_NONE);
	mRemoveCollider = false;
}