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
	, mShootSoundId(0)
	, mDamageCooldown(0.0f)
{

}
Ship::~Ship()
{

}

void Ship::Load()
{
	mImageId = X::LoadTexture("fighter.png");
	XASSERT(mImageId != 0, "Ship: image did not load");

	mShootSoundId = X::LoadSound("lazer-gun.wav");
	XASSERT(mShootSoundId != 0, "Ship: sound did not load");

	mPosition.x = X::GetScreenWidth() * 0.5f;
	mPosition.y = X::GetScreenHeight() * 0.5f;

	SetCollisionFilter(ET_ENEMY | ET_BULLET_ENEMY | ET_BULLET_BOSS);

	mHealth = mMaxHealth;
	mExplosion = new AnimSpriteSheet();
	mExplosion->Load();

	mDamageCooldown = 0.0f;
}
void Ship::Update(float deltaTime)
{
	if (mDamageCooldown > 0.0f)
	{
		mDamageCooldown -= deltaTime;
	}

	if (IsAlive())
	{
		// mouse rotation 
		float mouseX = X::GetMouseScreenX();
		float mouseY = X::GetMouseScreenY();

		X::Math::Vector2 mousePos(mouseX, mouseY);
		X::Math::Vector2 directionToMouse = mousePos - mPosition;

		mRotation = atan2(directionToMouse.y, directionToMouse.x) + X::Math::kPiByTwo;

		const float speed = 300.0f;

		if (X::IsKeyDown(X::Keys::W))
		{
			mPosition += X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
		}
		if (X::IsKeyDown(X::Keys::S))
		{
			mPosition -= X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
		}

		if (X::IsKeyPressed(X::Keys::SPACE))
		{
			X::Math::Vector2 spawnpos = mPosition + X::Math::Vector2::Forward(mRotation);
			Bullet* bullet = mBulletPool->GetBullet();
			bullet->SetEntityType(ET_BULLET_PLAYER);
			bullet->SetActive(spawnpos, mRotation, 2.0f);

			X::PlaySoundOneShot(mShootSoundId);
		}
	}
	
	mExplosion->Update(deltaTime);
}
void Ship::Render()
{
	if (IsAlive())
	{
		X::DrawSprite(mImageId, mPosition, mRotation);
		/*X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::Pink);*/
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
		if(collidable->GetType() == ET_POWERUP_HEALTH)
		{
			return; // No damage taken from health power-up
		}

		if (mDamageCooldown > 0.0f)
		{
			return;
		}

		int damage = 0;
		if (collidable->GetType() == ET_ENEMY)
		{
			if (collidable->GetRadius() > 50.0f)
			{
				damage = 30;
			}
			else
			{
				damage = 10;
			}
		}
		else if (collidable->GetType() == ET_BULLET_BOSS)
		{
			damage = 20;
		}
		else if (collidable->GetType() == ET_BULLET_ENEMY)
		{
			damage = 10;
		}
		mHealth -= damage;

		mDamageCooldown = 1.0f;

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

void Ship::SetHealth(int health)
{
	mHealth = health;
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
