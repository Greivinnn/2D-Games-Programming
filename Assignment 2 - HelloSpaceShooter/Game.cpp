#include "Game.h"
#include "Ship.h"
#include "Pool.h"
#include "Bullet.h"
#include "Enemy.h"
#include "ProgressBar.h"

//static int minSpawnAmount = 5;
//static int maxSpawnAmount = 10;
//static int spawnAmount = minSpawnAmount + rand() % (maxSpawnAmount - minSpawnAmount + 1);
//X::Math::Vector2 spawnPosition = X::Math::Vector2::Zero();
//X::Math::Vector2 spawnDirection = X::Math::Vector2::Zero();
//X::Math::Vector2 center = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
//const float minOffSet = 100.0f;
//const float maxOffSet = center.y;

Game::Game()
	:Entity()
	, mPlayer(nullptr)
	, mBulletPool(nullptr)
	, mHealthBar(nullptr)
	, mSurvivalTimer(0.0f)
	, mSurviveTimeGoal(30.0f)
	, mBossSpawned(false)
	, mMinSpawnAmount(2)
	, mMaxSpawnAmount(4)
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

	/*X::Math::Vector2 spawnPosition = X::Math::Vector2::Zero();	
	X::Math::Vector2 spawnDirection = X::Math::Vector2::Zero();	
	X::Math::Vector2 center = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
	const float minOffSet = 100.0f;
	const float maxOffSet = center.y;
	const int minSpawnAmount = 5;
	const int maxSpawnAmount = 10;
	int spawnAmount = minSpawnAmount + rand() % (maxSpawnAmount - minSpawnAmount + 1);
	for(int i = 0; i < spawnAmount; ++i)
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
	}*/

	SpawnWave();

	

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

	mSurvivalTimer += deltaTime;

	if(!mBossSpawned && AllEnemiesDead())
	{
		SpawnWave();
	}

	//if (!mBossSpawned && mSurvivalTimer >= mSurviveTimeGoal)
	//{
	//	mBossSpawned = true;

	//	// TODO: spawn boss here
	//	// for now spawn a BIG wave to feel like a boss
	//}

	//// assignemnt addition: check if all enemies are dead
	//if (enemy->AreAllEnemiesDead())
	//{
	//	minSpawnAmount = minSpawnAmount + 5;
	//	maxSpawnAmount = maxSpawnAmount + 10;

	//	for (int i = 0; i < spawnAmount; ++i)
	//	{
	//		spawnDirection = X::RandomUnitCircle();
	//		spawnPosition = center + (spawnDirection * X::RandomFloat(minOffSet, maxOffSet));

	//		Enemy* newEnemy = new Enemy();
	//		newEnemy->Load();
	//		newEnemy->SetBulletPool(mBulletPool);
	//		newEnemy->SetShip(mPlayer);
	//		newEnemy->SetPosition(spawnPosition);
	//		newEnemy->SetRotation(X::RandomFloat() * X::Math::kTwoPi);
	//		AddCollidable(newEnemy);
	//		mEnemies.push_back(newEnemy);
	//	}

	//	for (Enemy* enemy : mEnemies)
	//	{
	//		enemy->Update(deltaTime);
	//	}

	//	enemy->SetAllDeathEnemies(true);
	//}

	for (Enemy* enemy : mEnemies)
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

// assignemnt addition functions

void Game::SpawnWave()
{
	const float screenWidth = (float)X::GetScreenWidth();
	const float spawnY = 100.0f; // slightly above screen

	int spawnAmount = mMinSpawnAmount + rand() % (mMaxSpawnAmount - mMinSpawnAmount + 1);

	for (int i = 0; i < spawnAmount; ++i)
	{
		// spread enemies across the width of the screen
		float x = X::RandomFloat(50.0f, screenWidth - 50.0f);
		X::Math::Vector2 spawnPosition = { x, spawnY };

		Enemy* newEnemy = new Enemy();
		newEnemy->Load();
		newEnemy->SetBulletPool(mBulletPool);
		newEnemy->SetShip(mPlayer);
		newEnemy->SetPosition(spawnPosition);
		//// face downwards
		//newEnemy->SetRotation(X::Math::kPi * 0.5f);
		newEnemy->SetMovementSeed(X::RandomFloat(0.0f, 1000.0f));
		AddCollidable(newEnemy);
		mEnemies.push_back(newEnemy);
	}

	// make waves harder here:
	mMinSpawnAmount += 2;
	mMaxSpawnAmount += 4;
}

bool Game::AllEnemiesDead() const
{
	for (const Enemy* enemy : mEnemies)
	{
		if (enemy->IsAlive())
		{
			return false;
		}
	}
	return true;
}



