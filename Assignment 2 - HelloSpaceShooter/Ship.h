#pragma once
#include "Entity.h"
#include "Collidable.h";

class Pool;
class AnimSpriteSheet;

class Ship : public Entity, public Collidable
{
public:
	Ship();
	~Ship();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;
	 
	int GetType() const override;
	const X::Math::Vector2& GetPosition() const override;
	void OnCollision(Collidable* collidable) override;
	void SetBulletPool(Pool* bulletPool);

	int GetHealth() const;
	int GetMaxHealth() const;
	bool IsAlive() const;

private:
	X::TextureId mImageId;
	X::Math::Vector2 mPosition;
	float mRotation;
	int mHealth;
	int mMaxHealth;

	AnimSpriteSheet* mExplosion;
	Pool* mBulletPool;
};