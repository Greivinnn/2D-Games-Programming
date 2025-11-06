#include "HealthPowerUp.h"
#include "AnimSpriteSheet.h"
#include "Ship.h"

HealthPowerUp::HealthPowerUp()
	: Entity()
	, Collidable(15.0f)
	, mImageId(0)
	, mPosition(0.0f, 0.0f)
	, mRotation(0.0f)
	, mHealthBoost(0.0f)
	, mActive(false)
{
}

HealthPowerUp::~HealthPowerUp()
{
}

void HealthPowerUp::Load()
{
	mImageId = X::LoadTexture("mushroom.png");
	XASSERT(mImageId != 0, "HealthPowerUp: image did not load");
	SetCollisionFilter(ET_SHIP);
	mHealthBoost = 20.0f; 
}

void HealthPowerUp::Update(float deltaTime)
{
	if(!mActive)
	{
		return;
	}

	const float fallSpeed = 150.0f;
	mPosition.y += fallSpeed * deltaTime;

	const float screenH = (float)X::GetScreenHeight();
	if (mPosition.y > screenH + 50.0f)
	{
		SetActive(false);
	}
}

void HealthPowerUp::Render()
{
	if(!IsActive())
	{
		return;
	}
	X::DrawSprite(mImageId, mPosition, mRotation);
	X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::Lime);
}

void HealthPowerUp::Unload()
{
	
}

int HealthPowerUp::GetType() const
{
	return ET_POWERUP_HEALTH;
}

const X::Math::Vector2& HealthPowerUp::GetPosition() const
{
	return mPosition;
}

void HealthPowerUp::OnCollision(Collidable* collidable)
{
	if (IsActive())
	{
		if (collidable->GetType() == ET_SHIP)
		{
			Ship* ship = static_cast<Ship*>(collidable);
			int currentHealth = ship->GetHealth();
			int maxHealth = ship->GetMaxHealth();
			currentHealth += static_cast<int>(mHealthBoost);
			if (currentHealth > maxHealth)
			{
				currentHealth = maxHealth;
			}
			ship->SetHealth(currentHealth);
			SetActive(false);
		}
	}
}

void HealthPowerUp::SetHealthBoost(float healthBoost)
{
	mHealthBoost = healthBoost;
}

float HealthPowerUp::GetHealthBoost() const
{
	return mHealthBoost;
}

void HealthPowerUp::SetActive(bool active)
{
	mActive = active;
}

bool HealthPowerUp::IsActive() const
{
	return mActive;
}

void HealthPowerUp::SetPosition(const X::Math::Vector2& position)
{
	mPosition = position;
}