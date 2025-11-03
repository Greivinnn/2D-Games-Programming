#include "Ship.h"
#include "Bullet.h"
#include "Pool.h"
#include "AnimSpriteSheet.h"

Ship::Ship()
	:Entity()
	, Collidable(30.0f)
	, mImageId(0)
	, mPosition(0.0f)
	, mRotation(0.0f)
	, mHealth(0)
	, mMaxHealth(100)
	, mBulletPool(nullptr)
	, mExplosion(nullptr)
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

	mHealth = mMaxHealth;
	mExplosion = new AnimSpriteSheet();
	mExplosion->Load();
}
void Ship::Update(float deltaTime)
{
	if (IsAlive())
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
			bullet->SetEntityType(ET_BULLET_PLAYER);
			bullet->SetActive(spawnpos, mRotation, 2.0f);
		}
	}
	
	mExplosion->Update(deltaTime);
}
void Ship::Render()
{
	if (IsAlive())
	{
		X::DrawSprite(mImageId, mPosition, mRotation);
		X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::Pink);
	}
	mExplosion->Render();
}
void Ship::Unload() 
{
	mExplosion->Unload();
	delete mExplosion;
	mExplosion = nullptr;
}

int Ship::GetType() const
{
	return ET_SHIP;
}

void Ship::OnCollision(Collidable* collidable)
{
	if(IsAlive())
	{
		int damage = 0;
		if (collidable->GetType() == ET_ENEMY)
		{
			damage = 10;
			
		}
		else
		{
			damage = 2;
		}
		mHealth -= damage;

		if (!IsAlive())
		{
			mExplosion->SetActive(mPosition);
			SetCollisionFilter(0);
		}
	}
}

void Ship::SetBulletPool(Pool* bulletPool)
{
	mBulletPool = bulletPool;
}

const X::Math::Vector2& Ship::GetPosition() const
{
	return mPosition;
}

int Ship::GetHealth() const
{
	return mHealth;
}
int Ship::GetMaxHealth() const
{
	return mMaxHealth;
}
bool Ship::IsAlive() const
{
	return mHealth > 0;
}
