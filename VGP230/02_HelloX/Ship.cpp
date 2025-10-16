#include "Ship.h"
#include "Bullet.h"

Ship::Ship()
	:Entity()
	, mImageId(0)
	, mPosition(0.0f)
	, mRotation(0.0f)
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

	mBulletPool.Load();
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
		Bullet* bullet = mBulletPool.GetBullet();
		bullet->SetActive(spawnpos, mRotation, 2.0f);
	}
	mBulletPool.Update(deltaTime);
}
void Ship::Render()
{
	X::DrawSprite(mImageId, mPosition, mRotation);
	mBulletPool.Render();
}
void Ship::Unload() 
{
	mBulletPool.Unload();
}