#pragma once
#include "Entity.h"

class Bullet;

class BulletPool : public Entity
{
public:
	BulletPool();
	~BulletPool();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	Bullet* GetBullet();
	std::vector<Bullet*>& GetBullets();

private:
	int mNextAvailableIndex;
	std::vector<Bullet*> mBullets;
};

