#include "BossFight.h"
#include "Pool.h"
#include "Bullet.h"
#include "Ship.h"
#include "AnimSpriteSheet.h"

BossFight::BossFight()
	: Entity()
	, Collidable(60.0f)
	, mBulletPool(nullptr)
	, mShip(nullptr)
	, mExplosion(nullptr)
	, mImageId(0)
	, mPosition(0.0f, 0.0f)
	, mRotation(0.0f)
	, mHealth(500)
	, mCenterPoint(0.0f, 0.0f)
	, mTargetPosition(0.0f, 0.0f)
	, mTargetPositionUpdate(0.0f)
	, mFireRate(0.0f)
	, mShootSoundId(0)
	, mDamageCoolDown(0.0f)
{
}

BossFight::~BossFight()
{
}

//Entity override
void BossFight::Load()
{
	mImageId = X::LoadTexture("fighter1.png");
	XASSERT(mImageId > 0, "BossFight: image did not load");

	mShootSoundId = X::LoadSound("laser-gun-shot-Boss.wav");
	XASSERT(mShootSoundId > 0, "BossFight: sound did not load");

	mPosition = X::Math::Vector2::Zero();
	mRotation = 0.0f;
	SetCollisionFilter(ET_BULLET_PLAYER | ET_SHIP);
	mExplosion = new AnimSpriteSheet();
	mExplosion->Load();
	mTargetPositionUpdate = 0.0f;
	mFireRate = 3.0f;
	mDamageCoolDown = 0.0f;
}

void BossFight::Update(float deltaTime)
{
	if (IsAlive())
	{
		if (mDamageCoolDown > 0.0f)
		{
			mDamageCoolDown -= deltaTime;
		}

		const float speed = 50.0f;

		mTargetPositionUpdate -= deltaTime;
		if(mTargetPositionUpdate <= 0.0f)
		{
			// Pick new random position on screen
			float offsetX = X::RandomFloat(-200.0f, 200.0f);
			float offsetY = X::RandomFloat(-50.0f, 100.0f);
			mTargetPosition = mCenterPoint + X::Math::Vector2(offsetX, offsetY);
			mTargetPositionUpdate = X::RandomFloat(2.0f, 4.0f);
		}

		X::Math::Vector2 direction = mTargetPosition - mPosition;
		float distance = X::Math::Magnitude(direction);
		if (distance > 1.0f)
		{
			direction = X::Math::Normalize(direction);
			mPosition += direction * speed * deltaTime;
		}

		if (mShip && mShip->IsAlive())
		{
			X::Math::Vector2 dir = X::Math::Normalize(mShip->GetPosition() - mPosition);
			mRotation = atan2f(dir.x, -dir.y);
		}

		mFireRate -= deltaTime;
		if(mFireRate <= 0.0f && mShip->IsAlive())
		{
			const int bulletCount = 5;
			const float spreadAngle = X::Math::kPi * 0.3f; // 54 degrees

			X::Math::Vector2 toPlayer = X::Math::Normalize(mShip->GetPosition() - mPosition);
			float baseAngle = atan2f(toPlayer.x, -toPlayer.y);

			for (int i = 0; i < bulletCount; ++i)
			{
				float angle = baseAngle + (i - bulletCount / 2) * (spreadAngle / bulletCount);

				Bullet* bullet = mBulletPool->GetBullet();
				if(bullet != nullptr)
				{
					X::Math::Vector2 spawnPos = mPosition + X::Math::Vector2::Forward(angle) * 50.0f;

					bullet->SetEntityType(ET_BULLET_BOSS);
					bullet->SetActive(spawnPos, angle, 3.0f);
				}
			}
			mFireRate = X::RandomFloat(1.0f, 3.0f);
			X::PlaySoundOneShot(mShootSoundId);
		}
	}

	mExplosion->Update(deltaTime);
}

void BossFight::Render()
{
	if (IsAlive())
	{
		X::DrawSprite(mImageId, mPosition, mRotation);
		/*X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::AliceBlue);*/
	}
	mExplosion->Render();
}

void BossFight::Unload()
{
	mExplosion->Unload();
	delete mExplosion;
	mExplosion = nullptr;
}

// collidable override
int BossFight::GetType() const
{
	return ET_ENEMY;
}

const X::Math::Vector2& BossFight::GetPosition() const
{
	return mPosition;
}

void BossFight::OnCollision(Collidable* collidable)
{
	if (IsAlive())
	{
		int damage = 0;
		if (collidable->GetType() == ET_SHIP)
		{
			if (mDamageCoolDown <= 0)
			{
				damage = 20;
				mDamageCoolDown = 1.0f;
			}
		}
		else
		{
			damage = 10;
		}
		mHealth -= damage;
		if (!IsAlive())
		{
			mExplosion->SetActive(mPosition);
			SetCollisionFilter(0);
		}
	}

}

void BossFight::SetBulletPool(Pool* bulletPool)
{
	mBulletPool = bulletPool;
}

void BossFight::SetShip(Ship* ship)
{
	mShip = ship;
}

void BossFight::SetPosition(const X::Math::Vector2& position)
{
	mPosition = position;
}

void BossFight::SetRotation(float rotation)
{
	mRotation = rotation;
}

bool BossFight::IsAlive() const
{
	return mHealth > 0;
}

void BossFight::SetCenterPoint(const X::Math::Vector2& centerPoint)
{
	mCenterPoint = centerPoint;
	mTargetPosition = centerPoint;
}
