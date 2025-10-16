#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void SetActive(const X::Math::Vector2& pos, float rotation, float lifeTime = 2.0f);
	bool IsActive() const;
private:
	X::TextureId mImageId;
	X::Math::Vector2 mPosition;
	float mRotation;
	float mLifeTime;
};
