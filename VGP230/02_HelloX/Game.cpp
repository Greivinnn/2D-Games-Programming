#include "Game.h"
#include "Ship.h"
#include "Pool.h"
#include "Bullet.h"
#include "Enemy.h"
#include "ProgressBar.h"

Game::Game()
	:Entity()
	, mPlayer(nullptr)
	, mBulletPool(nullptr)
	, mHealthBar(nullptr)
{
}

Game::~Game()
{
	XASSERT(mPlayer == nullptr, "Game: Unload was not called");
}

void Game::Load()
{
	mPlayer = new Ship();
	mBulletPool = new Pool;
	mHealthBar = new ProgressBar();

	mPlayer->Load();
	mPlayer->SetBulletPool(mBulletPool);
	AddCollidable(mPlayer);

	mHealthBar->Load();

	X::Math::Vector2 spawnPosition = X::Math::Vector2::Zero();	
	X::Math::Vector2 spawnDirection = X::Math::Vector2::Zero();	
	X::Math::Vector2 center = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
	const float minOffSet = 100.0f;
	const float maxOffSet = center.y;
	for(int i = 0; i < 10; ++i)
	{
		spawnDirection = X::RandomUnitCircle();
		spawnPosition = center + (spawnDirection * X::RandomFloat(minOffSet, maxOffSet));

		Enemy* newEnemy = new Enemy();
		newEnemy->Load();
		newEnemy->SetBulletPool(mBulletPool);
		newEnemy->SetShip(mPlayer);
		newEnemy->SetPosition(spawnPosition);
		newEnemy->SetRotation(X::RandomFloat() * X::Math::kTwoPi);
		AddCollidable(newEnemy);
		mEnemies.push_back(newEnemy);
	}

	

	mBulletPool->Load();
	std::vector<Bullet*>& bullets = mBulletPool->GetBullets();
	for (Bullet* bullet : bullets)
	{
		AddCollidable(bullet);
	}


}

void Game::Update(float deltaTime)
{
	mPlayer->Update(deltaTime);
	for(Enemy* enemy : mEnemies)
	{
		enemy->Update(deltaTime);
	}
	mBulletPool->Update(deltaTime);

	int numCollidables = mCollidables.size();
	for (int i = 0; i < numCollidables; ++i)
	{
		for (int n = i + 1; n < numCollidables; ++n)
		{
			if (mCollidables[i]->DidCollide(mCollidables[n]))
			{
				mCollidables[i]->OnCollision(mCollidables[n]);
				mCollidables[n]->OnCollision(mCollidables[i]);
			}
		}
		
	}

	mHealthBar->SetBarValue(mPlayer->GetHealth(), mPlayer->GetMaxHealth());
}

void Game::Render()
{
	mPlayer->Render();
	for (Enemy* enemy : mEnemies)
	{
		enemy->Render();
	}
	mBulletPool->Render();
	mHealthBar->Render();
}

void Game::Unload()
{
	mBulletPool->Unload();
	delete mBulletPool;
	mBulletPool = nullptr;

	mHealthBar->Unload();
	delete mHealthBar;
	mHealthBar = nullptr;

	mPlayer->Unload();
	delete mPlayer;
	mPlayer = nullptr;

	for (Enemy* enemy : mEnemies)
	{
		enemy->Unload();
		delete enemy;
		enemy = nullptr;
	}
	mEnemies.clear();
}

void Game::AddCollidable(Collidable* collidable)
{
	mCollidables.push_back(collidable);
}

bool Game::IsGameOver()
{
	return !mPlayer->IsAlive();
}
