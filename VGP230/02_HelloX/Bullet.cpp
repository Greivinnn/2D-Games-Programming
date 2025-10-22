#include "Bullet.h"

Bullet::Bullet()
	: Entity()
	, Collidable(10.0f)
	, mImageId(0)
	, mPosition(0.0f)
	, mRotation(0.0f)
	, mLifeTime(0.0f)
	, mBulletType(ET_ALL)
{
}

Bullet::~Bullet()
{
}

void Bullet::Load()
{
	mImageId = X::LoadTexture("bullet1.png");
}

void Bullet::Update(float deltaTime)
{
	if (IsActive())
	{
		mLifeTime -= deltaTime;
		const float speed = 200.0f;
		mPosition += X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
		if (!IsActive())
		{
			SetCollisionFilter(ET_NONE);
		}
	}
}

void Bullet::Render()
{
	if (IsActive())
	{
		X::DrawSprite(mImageId, mPosition, mRotation);	
		X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::Yellow);  
	}
}

void Bullet::Unload()
{
}

void Bullet::SetActive(const X::Math::Vector2& pos, float rotation, float lifeTime)
{
	mPosition = pos;
	mRotation = rotation;
	mLifeTime = lifeTime;
}

void Bullet::SetEntityType(EntityType type)
{
	mBulletType = type;
}

bool Bullet::IsActive() const
{
	return mLifeTime > 0.0f;
}

int Bullet::GetType() const
{
	return 0;
}

const X::Math::Vector2& Bullet::GetPosition() const
{
	return 0;
}

void Bullet::OnCollision(Collidable* collidable)
{
	mLifeTime = 0.0f;
	SetCollisionFilter(ET_NONE);
}
