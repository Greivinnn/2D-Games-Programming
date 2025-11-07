#include "DiverEnemy.h"
#include "Pool.h"
#include "Bullet.h"
#include "Ship.h"
#include "AnimSpriteSheet.h"

DiverEnemy::DiverEnemy()
	: Entity()
	, Collidable(30.0f)
	, mBulletPool(nullptr)
	, mShip(nullptr)
	, mExplosion(nullptr)
	, mImageId(0)
	, mPosition(0.0f, 0.0f)
	, mRotation(0.0f)
	, mHealth(50)
	, mCenterPoint(0.0f, 0.0f)
	, mTargetPosition(0.0f, 0.0f)
	, mTargetPositionUpdate(0.0f)
	, mState(DiveState::Spawning)
	, mTimer(0.0f)
	, mWaitTime(0.0f)
	, mDiveSpeed(0.0f)
	, mDiveDirection(0.0f, 0.0f)
{
}

DiverEnemy::~DiverEnemy()
{
}

void DiverEnemy::Load()
{
	mImageId = X::LoadTexture("interceptor_01.png");
	XASSERT(mImageId > 0, "DiverEnemy: image did not load");

	float screenWidth = X::GetScreenWidth();

	// Random X across the top of the screen
	mPosition.x = X::RandomFloat(0.0f, screenWidth);
	mPosition.y = 50.0f; // top of screen

	mWaitTime = X::RandomFloat(1.0f, 3.0f); // random wait before dive
	mDiveSpeed = X::RandomFloat(200.0f, 400.0f); // random dive speed
	mState = DiveState::Waiting;

	SetCollisionFilter(ET_BULLET_PLAYER | ET_SHIP);

	mExplosion = new AnimSpriteSheet();
	mExplosion->Load();

}

void DiverEnemy::Update(float deltaTime)
{
	bool soundPlayed = false;
	if(!IsAlive())
	{
		mExplosion->Update(deltaTime);
		return;
	}
	mTimer += deltaTime;

	switch (mState)
	{
	case DiveState::Waiting:
		{
		mPosition.y += sinf(mTimer * 2.0f) * 10.0f * deltaTime; // slight up and down motion

			if (mTimer >= mWaitTime && mShip)
			{
				X::Math::Vector2 playerPos = mShip->GetPosition();	
				mDiveDirection = X::Math::Normalize(playerPos - mPosition);
				mRotation = atan2f(mDiveDirection.y, mDiveDirection.x) + X::Math::kPiByTwo;
				mState = DiveState::Diving;
			}
		}
		break;

		case DiveState::Diving:
		{
			// move straight in locked direction
			mPosition += mDiveDirection * mDiveSpeed * deltaTime;
			
			// if off screen, die
			float screenW = (float)X::GetScreenWidth();
			float screenH = (float)X::GetScreenHeight();

			if(mPosition.y > screenH + 50.0f || mPosition.y < -50.0f || mPosition.x < -50.0f || mPosition.x > screenW + 50.0f)
			{
				mHealth = 0;
				mExplosion->SetActive(mPosition);
				SetCollisionFilter(0);
				mState = DiveState::Dead;
			}
		}
		break;

		case DiveState::Dead:
			mExplosion->Update(deltaTime);
			break;
	}
}

void DiverEnemy::Render()
{
	if (IsAlive())
	{
		X::DrawSprite(mImageId, mPosition, mRotation);
		X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::AliceBlue);
	}
	mExplosion->Render();
}

void DiverEnemy::Unload()
{
	mExplosion->Unload();
	delete mExplosion;
	mExplosion = nullptr;
}

// collidable override
int DiverEnemy::GetType() const
{
	return ET_ENEMY;
}
const X::Math::Vector2& DiverEnemy::GetPosition() const
{
	return mPosition;
}
void DiverEnemy::OnCollision(Collidable* collidable)
{
	if (IsAlive())
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
		}
	}
}

//Enemy functions
void DiverEnemy::SetBulletPool(Pool* bulletPool)
{
	mBulletPool = bulletPool;
}
void DiverEnemy::SetShip(Ship* ship)
{
	mShip = ship;
}
void DiverEnemy::SetPosition(const X::Math::Vector2& position)
{
	mPosition = position;	
}
void DiverEnemy::SetRotation(float rotation)
{
	mRotation = rotation;
}
bool DiverEnemy::IsAlive() const
{
	return mHealth > 0;
}