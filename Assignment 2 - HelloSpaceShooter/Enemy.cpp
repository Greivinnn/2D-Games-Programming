#include "Enemy.h"
#include "Pool.h"
#include "Bullet.h"
#include "Ship.h"
#include "AnimSpriteSheet.h"

Enemy::Enemy()
	: Entity()
	, Collidable(30.0f)
	, mBulletPool(nullptr)
	, mShip(nullptr)
	, mExplosion(nullptr)
	, mImageId(0)
	, mPosition(0.0f, 0.0f)
	, mRotation(0.0f)
	, mHealth(100)
	, mCenterPoint(0.0f, 0.0f)
	, mTargetPosition(0.0f, 0.0f)
	, mTargetPositionUpdate(0.0f)
	, mFireRate(0.0f)
	, mTimer(0.0f)
	, mMovementSeed(0)
	, mHomeOffset(0.0f, 0.0f)
	, mHoverRadius(0.0f)
	, mJustDied(false)
	, mShootSoundId(0)
{}
Enemy::~Enemy()
{

}
//Entity override
void Enemy::Load()
{
	mImageId = X::LoadTexture("carrier_01.png");
	XASSERT(mImageId > 0, "Enemy: image did not load");

	mShootSoundId = X::LoadSound("laser-gun-enemies.wav");
	XASSERT(mShootSoundId > 0, "Enemy: sound did not load");

	mPosition = X::Math::Vector2::Zero();
	mRotation = 0.0f;

	SetCollisionFilter(ET_BULLET_PLAYER | ET_SHIP);

	mExplosion = new AnimSpriteSheet();
	mExplosion->Load();

	mTargetPositionUpdate = 0.0f;
	mFireRate = 5.0f;

}
void Enemy::Update(float deltaTime)
{
	float screenH = X::GetScreenHeight();
	if (mPosition.y > screenH + 100.0f)
	{
		mHealth = 0;
		return;
	}

	if (IsAlive())
	{
		const float speed = 70.0f;

		// Move toward target
		X::Math::Vector2 moveDir = X::Math::Normalize(mTargetPosition - mPosition);
		mPosition += moveDir * speed * deltaTime;

		// Pick new random point near current position occasionally (hovering)
		mTargetPositionUpdate -= deltaTime;
		if (mTargetPositionUpdate <= 0.0f || X::Math::MagnitudeSqr(mTargetPosition - mPosition) < 50.0f)
		{
			// Pick new random offset relative to each enemy's personal orbit anchor
			float angle = X::RandomFloat(0.0f, X::Math::kTwoPi);
			float radius = mHoverRadius;

			float offsetX = cosf(angle) * radius;
			float offsetY = sinf(angle) * radius * 0.6f; // squish vertical to look shooter-style

			// orbit around personal center
			mTargetPosition = mCenterPoint + mHomeOffset + X::Math::Vector2(offsetX, offsetY);

			mTargetPositionUpdate = X::RandomFloat(1.5f, 2.8f);
		}

		// Aim and shoot at player
		if (mShip && mShip->IsAlive())
		{
			X::Math::Vector2 dir = X::Math::Normalize(mShip->GetPosition() - mPosition);
			mRotation = atan2f(dir.x, -dir.y);

			mFireRate -= deltaTime;
			if (mFireRate <= 0.0f)
			{
				Bullet* bullet = mBulletPool->GetBullet();
				if (bullet)
				{
					X::Math::Vector2 spawnPos = mPosition + X::Math::Vector2::Forward(mRotation) * 50.0f;
					bullet->SetEntityType(ET_BULLET_ENEMY);
					bullet->SetActive(spawnPos, mRotation, 3.0f);
					mFireRate = X::RandomFloat(1.0f, 3.0f);

					X::PlaySoundOneShot(mShootSoundId);
				}
			}
		}
	}
	mExplosion->Update(deltaTime);
}
void Enemy::Render()
{
	if (IsAlive())
	{
		X::DrawSprite(mImageId, mPosition, mRotation);
		/*X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::AliceBlue);*/
		/*X::DrawScreenCircle(mCenterPoint, 200, X::Colors::Teal);*/
	}
	mExplosion->Render();
}
void Enemy::Unload()
{
	mExplosion->Unload();
	delete mExplosion;
	mExplosion = nullptr;
}

// collidable override
int Enemy::GetType() const
{
	return ET_ENEMY;
}
const X::Math::Vector2& Enemy::GetPosition() const
{
	return mPosition;
}
void Enemy::OnCollision(Collidable* collidable)
{
	if(IsAlive())
	{
		int damage = 0;
		if (collidable->GetType() == ET_SHIP)
		{
			damage = mHealth;
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
			mJustDied = true;
		}
	}
}

//Enemy functions
void Enemy::SetBulletPool(Pool* bulletPool)
{
	mBulletPool = bulletPool;
}
void Enemy::SetShip(Ship* ship)
{
	mShip = ship;
}
void Enemy::SetPosition(const X::Math::Vector2& position)
{
	mPosition = position;

	// center point
	mCenterPoint = position;

	// Random personal home offset
	mHomeOffset = X::Math::Vector2(X::RandomFloat(-120.0f, 120.0f),X::RandomFloat(-80.0f, 80.0f));

	// Personal hover radius so they don't stack
	mHoverRadius = X::RandomFloat(40.0f, 90.0f);

	// initial target = personal space
	mTargetPosition = mCenterPoint + mHomeOffset;
	mTargetPositionUpdate = 0.0f;
}
void Enemy::SetRotation(float rotation)
{
	mRotation = rotation;
}
bool Enemy::IsAlive() const
{
	return mHealth > 0;
}

void Enemy::SetMovementSeed(float seed)
{
	mMovementSeed = seed;
}

bool Enemy::JustDied() const
{
	return mJustDied;
}

void Enemy::ClearDeathFlag()
{
	mJustDied = false;
}