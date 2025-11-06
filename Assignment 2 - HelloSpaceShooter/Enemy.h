#pragma once
#include "Entity.h"
#include "Collidable.h"

class Pool;
class Ship;
class AnimSpriteSheet;

class Enemy : public Entity, public Collidable
{
public:
	Enemy();
	~Enemy() override;

	//Entity override
	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	// collidable override
	int GetType() const override;
	const X::Math::Vector2& GetPosition() const override;
	void OnCollision(Collidable* collidable) override;

	//Enemy functions
	void SetBulletPool(Pool* bulletPool);
	void SetShip(Ship* ship);
	void SetPosition(const X::Math::Vector2& position);
	void SetRotation(float rotation);

	bool IsAlive() const;

	// assignment addition functions	
	void SetMovementSeed(float seed);
	bool JustDied() const;
	void ClearDeathFlag();

private:
	Pool* mBulletPool;
	Ship* mShip;
	AnimSpriteSheet* mExplosion;

	X::TextureId mImageId;
	X::Math::Vector2 mPosition;
	float mRotation;

	int mHealth;

	X::Math::Vector2 mCenterPoint;
	X::Math::Vector2 mTargetPosition;
	float mTargetPositionUpdate;
	float mFireRate;

	// Assignment addition variables
	float mTimer;
	float mMovementSeed;
	X::Math::Vector2 mHomeOffset;
	float mHoverRadius;
	bool mJustDied;
};
