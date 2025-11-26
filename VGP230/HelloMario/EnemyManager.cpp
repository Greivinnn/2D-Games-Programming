#include "EnemyManager.h"
#include "TileMap.h"

EnemyManager* EnemyManager::mInstance = nullptr;

EnemyManager::EnemyManager()
	: Entity()
	, mNextAvailableIndex(0)
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
	for(int i = 0; i < maxEnemies; ++i)
	{
		Enemy* enemy = new Enemy();
		enemy->Load();
		mEnemies.push_back(enemy);
	}
	mNextAvailableIndex = 0;
}
void EnemyManager::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::RCONTROL))
	{
		SpawnEnemies(5);
	}
	for(Enemy* enemy : mEnemies)
	{
		enemy->Update(deltaTime);
	}
}
void EnemyManager::Render()
{
	for(Enemy* enemy : mEnemies)
	{
		enemy->Render();
	}
}
void EnemyManager::Unload()
{
	for(Enemy* enemy : mEnemies)
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



