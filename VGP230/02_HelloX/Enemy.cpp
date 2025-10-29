#include "Enemy.h"
#include "Pool.h"
#include "Bullet.h"
#include "Ship.h"

Enemy::Enemy()
	: Entity()
	, Collidable(30.0f)
	, mBulletPool(nullptr)
	, mShip(nullptr)
	, mImageId(0)
	, mPosition(0.0f, 0.0f)
	, mRotation(0.0f)
{}
Enemy::~Enemy()
{

}
//Entity override
void Enemy::Load()
{
	mImageId = X::LoadTexture("carrier_01.png");
	XASSERT(mImageId > 0, "Enemy: image did not load");

	mPosition = X::Math::Vector2::Zero();
	mRotation = 0.0f;

	SetCollisionFilter(ET_BULLET_PLAYER | ET_SHIP);
}
void Enemy::Update(float deltaTime)
{

}
void Enemy::Render()
{
	X::DrawSprite(mImageId, mPosition, mRotation);
	X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::AliceBlue);
}
void Enemy::Unload()
{

}

// collidable override
int Enemy::GetType() const
{

}
const Enemy::X::Math::Vector2& GetPosition() const
{
	return mPosition;
}
void Enemy::OnCollision(Collidable* collidable)
{

}

//Enemy functions
void Enemy::SetBulletPool(Pool* bulletPool)
{

}
void Enemy::SetShip(Ship* ship)
{

}
void Enemy::SetPosition(const X::Math::Vector2& position)
{

}
void Enemy::SetRotation(float rotation)
{

}