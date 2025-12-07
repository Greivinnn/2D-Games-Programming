#include "ProjectileManager.h"

ProjectileManager* ProjectileManager::mInstance = nullptr;
ProjectileManager::ProjectileManager()
	:Entity()
	, mNextAvailableIndex(0)
{

}
ProjectileManager::~ProjectileManager()
{

}
ProjectileManager* ProjectileManager::Get()
{
	if (mInstance == nullptr)
	{
		mInstance = new ProjectileManager();
	}
	return mInstance;
}

void ProjectileManager::Load()
{
	mNextAvailableIndex = 0;
	const int maxProjectiles = 100;
	for (int i = 0; i < maxProjectiles; ++i)
	{
		Projectile* newProjectile = new Projectile();
		newProjectile->Load();
		mProjectiles.push_back(newProjectile);
	}
}
void ProjectileManager::Update(float deltaTime)
{
	for (Projectile* projectile : mProjectiles)
	{
		projectile->Update(deltaTime);
	}
}
void ProjectileManager::Render()
{
	for (Projectile* projectile : mProjectiles)
	{
		projectile->Render();
	}
}
void ProjectileManager::Unload()
{
	for (Projectile* projectile : mProjectiles)
	{
		projectile->Unload();
		delete projectile;
		projectile = nullptr;
	}
	mProjectiles.clear();
}

Projectile* ProjectileManager::GetProjectile()
{
	XASSERT(!mProjectiles.empty(), "ProjectileManager: no projectile loaded");
	Projectile* nextProjectile = mProjectiles[mNextAvailableIndex];
	int lastAvailableIndex = mNextAvailableIndex;
	while (nextProjectile->IsActive())
	{
		mNextAvailableIndex = (mNextAvailableIndex + 1) % mProjectiles.size();
		nextProjectile = mProjectiles[mNextAvailableIndex];
		if (lastAvailableIndex == mNextAvailableIndex)
		{
			break;
		}
	}
	mNextAvailableIndex = (mNextAvailableIndex + 1) % mProjectiles.size();
	return nextProjectile;
}