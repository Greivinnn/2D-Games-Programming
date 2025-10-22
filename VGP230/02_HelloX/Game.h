#pragma once

#include "Entity.h"
#include <vector>

class Ship;
class Pool;
class Collidable;

class Game : public Entity
{
public:
	Game();
	~Game() override;

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void AddCollidable(Collidable* collidable);

	bool IsGameOver();
private:
	Ship* mPlayer;
	Pool* mBulletPool;
	std::vector<Collidable*> mCollidables;
};