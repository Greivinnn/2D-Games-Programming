#pragma once
#include "Entity.h"
#include "Pool.h"

class Ship : public Entity
{
public:
	Ship();
	~Ship();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;
	 
private:
	X::TextureId mImageId;
	X::Math::Vector2 mPosition;
	float mRotation;
	Pool mBulletPool;
	
};