#pragma once

#include "Entity.h"
#include "Collidable.h"

class AnimSpriteSheet;	
class Ship;

class HealthPowerUp : public Entity, public Collidable
{
public:
	HealthPowerUp();
	~HealthPowerUp() override;
	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	int GetType() const override;
	const X::Math::Vector2& GetPosition() const override;
	void OnCollision(Collidable* collidable) override;

	void SetHealthBoost(float healthBoost);
	float GetHealthBoost() const;
	void SetActive(bool active);
	bool IsActive() const;
	void SetPosition(const X::Math::Vector2& position);

private:
	X::TextureId mImageId;
	X::Math::Vector2 mPosition;
	float mRotation;
	float mHealthBoost;
	bool mActive;
};