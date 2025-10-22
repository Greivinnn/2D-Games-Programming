#include "Ship.h"
#include "Bullet.h"
#include "Pool.h"

Ship::Ship()
	:Entity()
	, Collidable(30.0f)
	, mImageId(0)
	, mPosition(0.0f)
	, mRotation(0.0f)
	, mBulletPool(nullptr)
{

}
Ship::~Ship()
{

}

void Ship::Load()
{
	mImageId = X::LoadTexture("fighter.png");
	XASSERT(mImageId != 0, "Ship: image did not load");

	mPosition.x = X::GetScreenWidth() * 0.5f;
	mPosition.y = X::GetScreenHeight() * 0.5f;

	SetCollisionFilter(ET_ENEMY | ET_BULLET_ENEMY);
}
void Ship::Update(float deltaTime)
{
	const float speed = 100.0f;
	const float turnSpeed = X::Math::kPiByTwo;
	if (X::IsKeyDown(X::Keys::W))
	{
		mPosition += X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::S))
	{
		mPosition -= X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::A))
	{
		mRotation -= turnSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::D))
	{
		mRotation += turnSpeed * deltaTime;
	}
	
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		X::Math::Vector2 spawnpos = mPosition + X::Math::Vector2::Forward(mRotation);
		Bullet* bullet = mBulletPool->GetBullet();
		bullet->SetCollisionFilter(ET_BULLET_PLAYER);
		bullet->SetActive(spawnpos, mRotation, 2.0f);
	}
}
void Ship::Render()
{
	X::DrawSprite(mImageId, mPosition, mRotation);
	X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::Pink);
}
void Ship::Unload() 
{
}

int Ship::GetType() const
{
	return ET_SHIP;
}

void Ship::OnCollision(Collidable* collidable)
{
	XLOG("Ship hit something");
}

void Ship::BulletPool(Pool* bulletPool)
{
	mBulletPool = bulletPool;
}

const X::Math::Vector2& Ship::GetPosition() const
{
	return mPosition;
}
