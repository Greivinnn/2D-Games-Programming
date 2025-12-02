#include "Enemy.h"
#include "Enum.h"
#include "TileMap.h"
#include "CollisionManager.h"

Enemy::Enemy()
	: Entity()
	, Collidable()
	, mImageID(0)
	, mPosition(0.0f, 0.0f)
	, mCenterPoint(0.0f, 0.0f)
	, mTargetPoint(0.0f, 0.0f)
	, mTargetPosition(0.0f, 0.0f)
	, mEnemyRect(0, 0, 0, 0)
	, mTargetPointUpdate(0.0f)
	, mHealth(0)
	, mRemoveCollider(false)
{

}
Enemy::~Enemy()
{

}

void Enemy::Load()
{
	mImageID = X::LoadTexture("zombieHead.png");
	mTargetPointUpdate = 0.0f;	
	mHealth--;
	mRemoveCollider = false;

	float halfWidth = X::GetSpriteWidth(mImageID) * 0.5f;
	float halfHeight = X::GetSpriteHeight(mImageID) * 0.5f;
	mEnemyRect.left = -halfWidth;
	mEnemyRect.right = halfWidth;
	mEnemyRect.top = -halfHeight;
	mEnemyRect.bottom = halfHeight;
}
void Enemy::Update(float deltaTime)
{
	if (mRemoveCollider)
	{
		CollisionManager::Get()->RemoveCollidable(this);
		mRemoveCollider = false;
	}
	if(!IsActive())
	{
		return;
	}

	const float speed = 70.0f;
	const float offsetDistance = 200.0f;
	mTargetPointUpdate -= deltaTime;
	if(mTargetPointUpdate <= 0.0f || X::Math::Vector2::SqrMagnitude(mTargetPoint - mPosition) <= 100.0f)
	{
		mTargetPoint = mCenterPoint + (X::RandomUnitCircle() * offsetDistance);
		mTargetPointUpdate = X::RandomFloat(1.0f, 5.0f);
	}

	X::Math::Vector2 direction = X::Math::Normalize(mTargetPoint - mPosition);
	if (X::Math::Vector2::SqrMagnitude(direction) > 0.0f)
	{
		X::Math::Vector2 displacement = direction * speed * deltaTime;
		X::Math::Vector2 maxDisplacement = displacement;
		X::Math::Rect currentRect = mEnemyRect;
		currentRect.min += mPosition;
		currentRect.max += mPosition;
		if(TileMap::Get()->HasCollision(currentRect, maxDisplacement, displacement))
		{
			mPosition += displacement;
			if (X::Math::Vector2::SqrMagnitude(displacement) <= 10.0f)
			{
				mTargetPointUpdate = 0.0f;
			}
		}
		else
		{
			mPosition += displacement;
		}
		currentRect = mEnemyRect;
		currentRect.min += mPosition;
		currentRect.max += mPosition;
		SetRect(currentRect);
	}
}
void Enemy::Render()
{
	if(IsActive())
	{
		X::DrawSprite(mImageID, mPosition);
	}
}
void Enemy::Unload()
{

}

int Enemy::GetType() const
{
	return (IsActive()) ? ET_ENEMY : ET_NONE;
}
const X::Math::Vector2& Enemy::GetPosition() const
{
	return mPosition;
}

void Enemy::OnCollision(Collidable* collidable)
{
	if (IsActive())
	{
		if (collidable->GetType() == ET_PLAYER)
		{
			mHealth = 0;
			mRemoveCollider = true;
		}
		else if (collidable->GetType() == ET_BULLET)
		{
			mHealth = 0;
			mRemoveCollider = true;
		}
	}
}

bool Enemy::IsActive() const
{
	return mHealth > 0;
}
void Enemy::SetActive(const X::Math::Vector2& position, int health)
{
	mPosition = position;
	mCenterPoint = position;
	mTargetPoint = position;
	mTargetPointUpdate = 0.0f;
	mHealth = health;

	X::Math::Rect currentRect = mEnemyRect;
	currentRect.min += position;
	currentRect.max += position;
	SetRect(mEnemyRect);
	SetCollisionFilter(ET_PLAYER | ET_BULLET);

	CollisionManager::Get()->AddCollidable(this);
	mRemoveCollider = false;
}