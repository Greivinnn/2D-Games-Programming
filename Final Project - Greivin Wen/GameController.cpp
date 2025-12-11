#include "GameController.h"
#include "CollisionManager.h"
#include "PickupManager.h"
#include "TileMap.h"
#include "EnemyManager.h"

GameController* GameController::mInstance = nullptr;

GameController::GameController()
    : Entity()
{

}

GameController::~GameController()
{

}

GameController* GameController::Get()
{
    if (mInstance == nullptr)
    {
        mInstance = new GameController();
    }

    return mInstance;
}

void GameController::Load()
{
    CollisionManager::Get()->Load();
    TileMap::Get()->Load();
    PickupManager::Get()->Load();
    EnemyManager::Get()->Load();

    // Load bullet pool first
    mBulletPool.Load();

    // Then load player and give it the bullet pool
    mPlayer.Load();
    mPlayer.SetBulletPool(&mBulletPool);

    EnemyManager::Get()->SetPlayer(&mPlayer);
}

void GameController::Update(float deltaTime)
{
    TileMap::Get()->Update(deltaTime);
    PickupManager::Get()->Update(deltaTime);
    EnemyManager::Get()->Update(deltaTime);

    mBulletPool.Update(deltaTime);  // Update bullets
    mPlayer.Update(deltaTime);

    CollisionManager::Get()->Update(deltaTime);
}

void GameController::Render()
{
    TileMap::Get()->Render();
    PickupManager::Get()->Render();
    EnemyManager::Get()->Render();

    mBulletPool.Render();  // Render bullets
    mPlayer.Render();

    CollisionManager::Get()->Render();
}

void GameController::Unload()
{
    mPlayer.Unload();
    mBulletPool.Unload();  // Unload bullets
    PickupManager::Get()->Unload();
    EnemyManager::Get()->Unload();
    TileMap::Get()->Unload();
    CollisionManager::Get()->Unload();
}