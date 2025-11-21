#include "GameController.h"
#include "CollisionManager.h"
#include "PickupManager.h"
#include "TileMap.h"

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
    mPlayer.Load();
}

void GameController::Update(float deltaTime)
{
    TileMap::Get()->Update(deltaTime);
    PickupManager::Get()->Update(deltaTime);
    mPlayer.Update(deltaTime);

    CollisionManager::Get()->Update(deltaTime);
}

void GameController::Render()
{
    TileMap::Get()->Render();
    PickupManager::Get()->Render();
    mPlayer.Render();

    CollisionManager::Get()->Render();
}

void GameController::Unload()
{
    mPlayer.Unload();
    PickupManager::Get()->Unload();
    TileMap::Get()->Unload();
    CollisionManager::Get()->Unload();
}