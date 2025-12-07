#include "GameController.h"
#include "CollisionManager.h"
#include "PickupManager.h"
#include "TileMap.h"
#include "EnemyManager.h"
#include "ProjectileManager.h"

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
    ProjectileManager::Get()->Load();
    mPlayer.Load();
}

void GameController::Update(float deltaTime)
{
    TileMap::Get()->Update(deltaTime);
    PickupManager::Get()->Update(deltaTime);
	EnemyManager::Get()->Update(deltaTime);
    mPlayer.Update(deltaTime);

    ProjectileManager::Get()->Update(deltaTime);
    CollisionManager::Get()->Update(deltaTime);
}

void GameController::Render()
{
    TileMap::Get()->Render();
    PickupManager::Get()->Render();
	EnemyManager::Get()->Render();
    mPlayer.Render();

    ProjectileManager::Get()->Render();
    CollisionManager::Get()->Render();
}

void GameController::Unload()
{
    mPlayer.Unload();
    ProjectileManager::Get()->Unload();
    PickupManager::Get()->Unload();
	EnemyManager::Get()->Unload();
    TileMap::Get()->Unload();
    CollisionManager::Get()->Unload();
}