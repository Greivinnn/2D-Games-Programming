#include "GameController.h"
#include "CollisionManager.h"
#include "PickupManager.h"
#include "TileMap.h"
#include "EnemyManager.h"
#include <XEngine.h>

GameController* GameController::mInstance = nullptr;

GameController::GameController()
    : Entity()
    , mCurrentState(State::Start)
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

    // Start in Start state
    mCurrentState = State::Start;
}

void GameController::Update(float deltaTime)
{
    switch (mCurrentState)
    {
    case State::Start:
        UpdateStartScreen(deltaTime);
        break;

    case State::RunGame:
        UpdateRunGame(deltaTime);
        break;

    case State::End:
        UpdateEndScreen(deltaTime);
        break;
    }
}

void GameController::Render()
{
    switch (mCurrentState)
    {
    case State::Start:
        RenderStartScreen();
        break;

    case State::RunGame:
        RenderRunGame();
        break;

    case State::End:
        RenderEndScreen();
        break;
    }
}

void GameController::Unload()
{
    mPlayer.Unload();
    mBulletPool.Unload();
    PickupManager::Get()->Unload();
    EnemyManager::Get()->Unload();
    TileMap::Get()->Unload();
    CollisionManager::Get()->Unload();
}

void GameController::ChangeState(State newState)
{
    mCurrentState = newState;

    // Handle state entry logic
    if (newState == State::RunGame)
    {
        // Reset game when starting a new game
        mPlayer.Reset();  // You'll need to implement this in Player class
        EnemyManager::Get()->Reset();
        PickupManager::Get()->Reset();
        mBulletPool.Reset();
    }
}

void GameController::UpdateStartScreen(float deltaTime)
{
    // Check for input to start the game
    if (X::IsKeyPressed(X::Keys::SPACE) || X::IsKeyPressed(X::Keys::ENTER))
    {
        ChangeState(State::RunGame);
    }
}

void GameController::UpdateRunGame(float deltaTime)
{
    TileMap::Get()->Update(deltaTime);
    PickupManager::Get()->Update(deltaTime);
    EnemyManager::Get()->Update(deltaTime);

    mBulletPool.Update(deltaTime);
    mPlayer.Update(deltaTime);

    CollisionManager::Get()->Update(deltaTime);

    // Check if player is dead
    if (mPlayer.IsDead())  // You'll need to implement this in Player class
    {
        ChangeState(State::End);
    }
}

void GameController::UpdateEndScreen(float deltaTime)
{
    // Check for input to restart or quit
    if (X::IsKeyPressed(X::Keys::SPACE) || X::IsKeyPressed(X::Keys::ENTER))
    {
        ChangeState(State::RunGame);
    }
}

void GameController::RenderStartScreen()
{
    // Render the start screen
    X::DrawScreenText("GAME TITLE", X::GetScreenWidth() / 2 - 100, X::GetScreenHeight() / 2 - 50, 40, X::Colors::White);
    X::DrawScreenText("Press SPACE or ENTER to Start", X::GetScreenWidth() / 2 - 150, X::GetScreenHeight() / 2 + 50, 20, X::Colors::White);
}

void GameController::RenderRunGame()
{
    TileMap::Get()->Render();
    PickupManager::Get()->Render();
    EnemyManager::Get()->Render();

    mBulletPool.Render();
    mPlayer.Render();

    CollisionManager::Get()->Render();
}

void GameController::RenderEndScreen()
{
    // Render game over screen with the game state in background
    RenderRunGame();  // Show the game state behind

    // Draw semi-transparent overlay
    // Note: You might need to implement a filled rectangle function or use a sprite

    // Draw game over text
    X::DrawScreenText("GAME OVER", X::GetScreenWidth() / 2 - 100, X::GetScreenHeight() / 2 - 50, 40, X::Colors::Red);
    X::DrawScreenText("Press SPACE or ENTER to Restart", X::GetScreenWidth() / 2 - 180, X::GetScreenHeight() / 2 + 50, 20, X::Colors::White);
}

State GameController::GetCurrentState() const
{
    return mCurrentState;
}