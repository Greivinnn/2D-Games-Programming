#include "Pool.h"
#include "Bullet.h"

Pool::Pool()
	: Entity()
	, mNextAvailableIndex(0)
{
}

Pool::~Pool()
{
	XASSERT(mBullets.empty(), "BulletPool: Unload must be called");
		
}

void Pool::Load()
{
	const int maxBullets = 50;
	for (int i = 0; i < maxBullets; ++i)
	{
		Bullet* newBullet = new Bullet();
		newBullet->Load();
		mBullets.push_back(newBullet);
	}
}

void Pool::Update(float deltaTime)
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Update(deltaTime);
	}
}

void Pool::Render()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Render();
	}
}

void Pool::Unload()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Unload();
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
	mBullets.clear();
}

Bullet* Pool::GetBullet()
{
	Bullet* bullet = mBullets[mNextAvailableIndex];
	mNextAvailableIndex = (mNextAvailableIndex + 1) % mBullets.size();

	return bullet;
}

std::vector<Bullet*>& Pool::GetBullets()
{
	return mBullets;
}
