#include "PickupManager.h"
#include "TileMap.h"

PickupManager* PickupManager::mInstance = nullptr;

PickupManager::PickupManager()
    : Entity()
    , mNextAvailableIndex(0)
    , mSpawnTimer(0.0f)
    , mSpawnInterval(5.0f)  
    , mMaxActivePickups(5)   
{

}

PickupManager::~PickupManager()
{

}

PickupManager* PickupManager::Get()
{
    if (mInstance == nullptr)
    {
        mInstance = new PickupManager();
    }

    return mInstance;
}

void PickupManager::Load()
{
    const int maxPickups = 100;

    for (int i = 0; i < maxPickups; ++i)
    {
        Pickup* pickup = new Pickup();
        pickup->Load();
        mPickups.push_back(pickup);
    }

    mNextAvailableIndex = 0;
    mSpawnTimer = 2.0f;  
}

void PickupManager::Update(float deltaTime)
{
    // Auto spawn system
    mSpawnTimer -= deltaTime;

    if (mSpawnTimer <= 0.0f)
    {
        int activePickups = GetActivePickupCount();

        if (activePickups < mMaxActivePickups)
        {
            SpawnPickup(1);  

            mSpawnInterval = X::RandomFloat(3.0f, 7.0f);
        }

        mSpawnTimer = mSpawnInterval;
    }

    for (Pickup* pickup : mPickups)
    {
        pickup->Update(deltaTime);
    }
}

void PickupManager::Render()
{
    for (Pickup* pickup : mPickups)
    {
        pickup->Render();
    }
}

void PickupManager::Unload()
{
    for (Pickup* pickup : mPickups)
    {
        pickup->Unload();
        delete pickup;
        pickup = nullptr;
    }

    mPickups.clear();
}

void PickupManager::SpawnPickup(int count)
{
    std::vector<Tile*> walkableTiles;
    TileMap::Get()->ObtainAllWalkableTiles(walkableTiles);

    // Remove occupied tiles
    for (Pickup* pickup : mPickups)
    {
        if (pickup->IsActive() == true)
        {
            for (int i = 0; i < walkableTiles.size(); ++i)
            {
                if (walkableTiles[i]->HasCollision(pickup->GetRect()))
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

    for (int i = 0; i < count; ++i)
    {
        prevUsedIndex = mNextAvailableIndex - 1;

        if (prevUsedIndex < 0)
        {
            prevUsedIndex = mPickups.size() - 1;
        }

        while (mNextAvailableIndex != prevUsedIndex)
        {
            Pickup* pickup = mPickups[mNextAvailableIndex];
            mNextAvailableIndex = (mNextAvailableIndex + 1) % mPickups.size();

            if (pickup->IsActive() == false)
            {
                int randomIndex = X::Random(0, walkableTiles.size() - 1);
                Tile* randomTile = walkableTiles[randomIndex];
                pickup->SetActive(randomTile->GetPosition());

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

int PickupManager::GetActivePickupCount() const
{
    int count = 0;
    for (const Pickup* pickup : mPickups)
    {
        if (pickup->IsActive())
        {
            count++;
        }
    }
    return count;
}