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
    , mTitleScreen(0)
	, mTitleSound(0)
    , mPressSound(0)
	, mStartPlaying(false)
	, mRunGameSound(0)
	, mRunGamePlaying(false)
	, mGameOverSound(0)
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

    mBulletPool.Load();

    mPlayer.Load();
    mPlayer.SetBulletPool(&mBulletPool);

    EnemyManager::Get()->SetPlayer(&mPlayer);

    mCurrentState = State::Start;
	mTitleScreen = X::LoadTexture("FinalTitleScreen.png");
    mTitleSound = X::LoadSound("FinalProjectTittleMusic.wav");
    mRunGameSound = X::LoadSound("RunGameSound.wav");
    mPressSound = X::LoadSound("game-start.wav");
    mGameOverSound = X::LoadSound("GameOver.wav");
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

    if (newState == State::RunGame)
    {
        mPlayer.Reset(); 
        EnemyManager::Get()->Reset();
        PickupManager::Get()->Reset();
        mBulletPool.Reset();
    }
}

void GameController::UpdateStartScreen(float deltaTime)
{
	mStartPlaying = true;
    PlayTitleSound();
    if (X::IsKeyPressed(X::Keys::SPACE) || X::IsKeyPressed(X::Keys::ENTER))
    {
		mStartPlaying = false;
		PlayTitleSound();
        X::PlaySoundOneShot(mPressSound);
        ChangeState(State::RunGame);
    }
}

void GameController::UpdateRunGame(float deltaTime)
{
	mRunGamePlaying = true;
    PlayRunGameSound();
    TileMap::Get()->Update(deltaTime);
    PickupManager::Get()->Update(deltaTime);
    EnemyManager::Get()->Update(deltaTime);

    mBulletPool.Update(deltaTime);
    mPlayer.Update(deltaTime);

    CollisionManager::Get()->Update(deltaTime);

    if (mPlayer.IsDead()) 
    {
        mRunGamePlaying = false;
        PlayRunGameSound();
        ChangeState(State::End);
    }
}

void GameController::UpdateEndScreen(float deltaTime)
{
    if (X::IsKeyPressed(X::Keys::SPACE) || X::IsKeyPressed(X::Keys::ENTER))
    {
        ChangeState(State::RunGame);
    }
}

void GameController::RenderStartScreen()
{
    X::Math::Vector2 backgroundPos = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
    X::DrawSprite(mTitleScreen, backgroundPos);
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
    RenderRunGame();  

    X::DrawScreenText("GAME OVER", X::GetScreenWidth() / 2 - 100, X::GetScreenHeight() / 2 - 50, 40, X::Colors::Red);
    X::DrawScreenText("Press SPACE or ENTER to Restart", X::GetScreenWidth() / 2 - 180, X::GetScreenHeight() / 2 + 50, 20, X::Colors::White);
}

State GameController::GetCurrentState() const
{
    return mCurrentState;
}

void GameController::PlayTitleSound()
{
    if (mStartPlaying)
    {
        X::PlaySoundLoop(mTitleSound);
    }
    else
    {
        X::StopSoundLoop(mTitleSound);
    }
}

void GameController::PlayRunGameSound()
{
    if (mRunGamePlaying)
    {
        X::PlaySoundLoop(mRunGameSound);
    }
    else
    {
        X::StopSoundLoop(mRunGameSound);
    }
}
