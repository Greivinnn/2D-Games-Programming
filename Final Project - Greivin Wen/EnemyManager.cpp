#include "EnemyManager.h"
#include "TileMap.h"

EnemyManager* EnemyManager::mInstance = nullptr;

EnemyManager::EnemyManager()
	: Entity()
	, mNextAvailableIndex(0)
	, mCurrentWave(0)
	, mEnemiesPerWave(3)  
	, mWaveStartDelay(0.0f)  
	, mWaveActive(false)
{
}

EnemyManager::~EnemyManager()
{
}

EnemyManager* EnemyManager::Get()
{
	if (mInstance == nullptr)
	{
		mInstance = new EnemyManager();
	}
	return mInstance;
}

void EnemyManager::Load()
{
	const int maxEnemies = 100;
	for (int i = 0; i < maxEnemies; ++i)
	{
		Enemy* enemy = new Enemy();
		enemy->Load();
		mEnemies.push_back(enemy);
	}
	mNextAvailableIndex = 0;

	// Initialize wave system
	mCurrentWave = 0;
	mEnemiesPerWave = 6;
	mWaveStartDelay = 3.0f;  
	mWaveActive = false;
}

void EnemyManager::Update(float deltaTime)
{
	// Wave system logic
	if (!mWaveActive)
	{
		// Countdown to next wave
		mWaveStartDelay -= deltaTime;
		if (mWaveStartDelay <= 0.0f)
		{
			StartNextWave();
		}
	}
	else
	{
		// Check if wave is complete
		CheckWaveComplete();
	}

	// Update all enemies
	for (Enemy* enemy : mEnemies)
	{
		enemy->Update(deltaTime);
	}
}

void EnemyManager::Render()
{
	for (Enemy* enemy : mEnemies)
	{
		enemy->Render();
	}

	if (!mWaveActive && mWaveStartDelay > 0.0f)
	{
		char buffer[128];
		if (mCurrentWave == 0)
		{
			sprintf_s(buffer, "Wave 1 starting in %.1f seconds...", mWaveStartDelay);
		}
		else
		{
			sprintf_s(buffer, "Wave %d starting in %.1f seconds...", mCurrentWave + 1, mWaveStartDelay);
		}

		float fontSize = 36.0f; 
		float textWidth = X::GetTextWidth(buffer, fontSize);
		float centerX = (1280.0f - textWidth) * 0.5f;
		float yPos = 30.0f;

		X::DrawScreenText(buffer, centerX + 3.0f, yPos + 3.0f, fontSize, X::Colors::Black);  
		X::DrawScreenText(buffer, centerX - 1.0f, yPos - 1.0f, fontSize, X::Colors::Black);  
		X::DrawScreenText(buffer, centerX + 1.0f, yPos - 1.0f, fontSize, X::Colors::Black);  
		X::DrawScreenText(buffer, centerX - 1.0f, yPos + 1.0f, fontSize, X::Colors::Black);  
		X::DrawScreenText(buffer, centerX + 1.0f, yPos + 1.0f, fontSize, X::Colors::Black);  

		X::DrawScreenText(buffer, centerX, yPos, fontSize, X::Colors::Yellow);
	}
	else if (mWaveActive)
	{
		char buffer[128];
		sprintf_s(buffer, "Wave %d - Enemies: %d", mCurrentWave, GetAliveEnemyCount());

		float fontSize = 36.0f; 
		float textWidth = X::GetTextWidth(buffer, fontSize);
		float centerX = (1280.0f - textWidth) * 0.5f;
		float yPos = 30.0f;

		X::DrawScreenText(buffer, centerX + 3.0f, yPos + 3.0f, fontSize, X::Colors::Black);  
		X::DrawScreenText(buffer, centerX - 1.0f, yPos - 1.0f, fontSize, X::Colors::Black);  
		X::DrawScreenText(buffer, centerX + 1.0f, yPos - 1.0f, fontSize, X::Colors::Black);  
		X::DrawScreenText(buffer, centerX - 1.0f, yPos + 1.0f, fontSize, X::Colors::Black);  
		X::DrawScreenText(buffer, centerX + 1.0f, yPos + 1.0f, fontSize, X::Colors::Black);  

		X::DrawScreenText(buffer, centerX, yPos, fontSize, X::Colors::Yellow);
	}
}

void EnemyManager::Unload()
{
	for (Enemy* enemy : mEnemies)
	{
		enemy->Unload();
		delete enemy;
		enemy = nullptr;
	}
	mEnemies.clear();
}

void EnemyManager::SpawnEnemies(int amount)
{
	std::vector<Tile*> walkableTiles;
	TileMap::Get()->ObtainAllWalkableTiles(walkableTiles);

	// Remove occupied tiles
	for (Enemy* enemy : mEnemies)
	{
		if (enemy->IsActive() == true)
		{
			for (int i = 0; i < walkableTiles.size(); ++i)
			{
				if (walkableTiles[i]->HasCollision(enemy->GetRect()))
				{
					if (i < walkableTiles.size() - 1)
					{
						Tile* temp = walkableTiles[walkableTiles.size() - 1];
						walkableTiles[walkableTiles.size() - 1] = walkableTiles[i];
						walkableTiles[i] = temp;
					}

					walkableTiles.pop_back();
					break;
				}
			}
		}
	}

	int prevUsedIndex = 0;

	for (int i = 0; i < amount; ++i)
	{
		prevUsedIndex = mNextAvailableIndex - 1;

		if (prevUsedIndex < 0)
		{
			prevUsedIndex = mEnemies.size() - 1;
		}

		while (mNextAvailableIndex != prevUsedIndex)
		{
			Enemy* enemy = mEnemies[mNextAvailableIndex];
			mNextAvailableIndex = (mNextAvailableIndex + 1) % mEnemies.size();

			if (enemy->IsActive() == false)
			{
				int randomIndex = X::Random(0, walkableTiles.size() - 1);
				Tile* randomTile = walkableTiles[randomIndex];
				enemy->SetActive(randomTile->GetPosition(), 10);

				if (randomIndex < walkableTiles.size() - 1)
				{
					Tile* temp = walkableTiles[walkableTiles.size() - 1];
					walkableTiles[walkableTiles.size() - 1] = walkableTiles[randomIndex];
					walkableTiles[randomIndex] = temp;
				}

				walkableTiles.pop_back();
				break;
			}
		}
	}
}

void EnemyManager::StartNextWave()
{
	mCurrentWave++;
	mWaveActive = true;

	SpawnEnemies(mEnemiesPerWave);

	mEnemiesPerWave += 2; 
}

void EnemyManager::CheckWaveComplete()
{
	int aliveCount = GetAliveEnemyCount();

	if (aliveCount == 0)
	{
		mWaveActive = false;
		mWaveStartDelay = 3.0f;
	}
}

int EnemyManager::GetCurrentWave() const
{
	return mCurrentWave;
}

int EnemyManager::GetAliveEnemyCount() const
{
	int count = 0;
	for (const Enemy* enemy : mEnemies)
	{
		if (enemy->IsActive())
		{
			count++;
		}
	}
	return count;
}

void EnemyManager::SetPlayer(Player* player)
{
	for (Enemy* enemy : mEnemies)
	{
		enemy->SetPlayer(player);
	}
}

void EnemyManager::Reset()
{
	// Deactivate all enemies
	for (Enemy* enemy : mEnemies)
	{
		enemy->SetInactive();
	}

	// Reset pool index
	mNextAvailableIndex = 0;

	// Reset wave system to beginning
	mCurrentWave = 0;
	mEnemiesPerWave = 6;
	mWaveStartDelay = 3.0f;
	mWaveActive = false;
}
