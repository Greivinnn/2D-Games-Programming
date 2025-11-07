#pragma once

#include "Entity.h"
#include <vector>

class Ship;
class Pool;
class Collidable;
class Enemy;
class ProgressBar;
class DiverEnemy;	
class HealthPowerUp;

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

	// assignemnt addition functions
	void SpawnWave();
	bool AllEnemiesDead() const;
	void SpawnDiverEnemy();
	void SpawnHealthPowerUp(const X::Math::Vector2& position);
	void BossFight();
private:
	Ship* mPlayer;
	Pool* mBulletPool;
	std::vector<Collidable*> mCollidables;

	std::vector<Enemy*> mEnemies;
	std::vector<Enemy*> mDeathEnemies;
	ProgressBar* mHealthBar;

	// assignment addition variables	
	float mSurvivalTimer;
	float mSurviveTimeGoal;
	bool mBossSpawned;
	int mMinSpawnAmount;
	int mMaxSpawnAmount;
	// diverEnemy variables 
	std::vector<DiverEnemy*> mDiverEnemies;
	float mNextDiverSpawnTime;
	int mDiverSpawnCount;
	int mMaxDiverEnemiesSpawn;
	// health powerup variables
	std::vector<HealthPowerUp*> mHealthPowerUps;
};