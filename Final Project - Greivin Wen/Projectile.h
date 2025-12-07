#pragma once
#include "Entity.h"
#include "Collidable.h"

class Projectile : public Entity, public Collidable
{
public:
	Projectile();
	~Projectile();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	int GetType() const override;
	void OnCollision(Collidable* collidable) override;
	const X::Math::Vector2& GetPosition() const override;

	void SetActive(const X::Math::Vector2& position, const X::Math::Vector2& direction, float lifeTime = 2.0);
	void SetEntityType(EntityType entityType);
	void SetFlip(X::Flip flip);
	bool IsActive() const;
private:
	X::TextureId mImageId;
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mDirection;
	X::Math::Rect mProjectileRect;
	X::Flip mFlip;
	float mLifeTime;
	EntityType mBulletType;
	bool mRemoveCollider;
};