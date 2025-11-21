#include "PickupManager.h"
#include "TileMap.h"

PickupManager* PickupManager::mInstance = nullptr;

PickupManager::PickupManager()
    : Entity(), mNextAvailableIndex(0)
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
}

void PickupManager::Update(float deltaTime)
{
    if (X::IsKeyPressed(X::Keys::P))
    {
        SpawnPickup(10);
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