#pragma once

#include "Enemy.h"

class EnemyManager : public Entity
{
public:
	~EnemyManager();
	static EnemyManager* Get();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void SpawnEnemies(int amount);

	// Wave system
	int GetCurrentWave() const;
	int GetAliveEnemyCount() const;

private:
	EnemyManager();
	static EnemyManager* mInstance;
	std::vector<Enemy*> mEnemies;
	int mNextAvailableIndex;

	// Wave system variables
	int mCurrentWave;
	int mEnemiesPerWave;
	float mWaveStartDelay;
	bool mWaveActive;

	void StartNextWave();
	void CheckWaveComplete();
};
