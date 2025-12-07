#pragma once

#include "Entity.h"
#include "Projectile.h"

class ProjectileManager : public Entity
{
public:
	~ProjectileManager();
	static ProjectileManager* Get();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	Projectile* GetProjectile();

	std::vector<Projectile*> mProjectiles;
	int mNextAvailableIndex;
private:
	ProjectileManager();
	static ProjectileManager* mInstance;
};
