#pragma once

#include "Entity.h"
#include "Collidable.h"


class Enemy : public Entity, public Collidable
{
public:
	Enemy();
	~Enemy();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	int GetType() const override;
	const X::Math::Vector2& GetPosition() const override;
	void OnCollision(Collidable* collidable) override;

	bool IsActive() const;
	void SetActive(const X::Math::Vector2& position, int health);

private:
	X::TextureId mImageID;
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mCenterPoint;
	X::Math::Vector2 mTargetPoint;
	X::Math::Vector2 mTargetPosition;
	X::Math::Rect mEnemyRect;
	float mTargetPointUpdate;
	int mHealth;
	bool mRemoveCollider;
};
