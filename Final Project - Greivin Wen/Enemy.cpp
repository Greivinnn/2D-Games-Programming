#include "Enemy.h"
#include "Enum.h"
#include "TileMap.h"
#include "CollisionManager.h"
#include "Player.h"

Enemy::Enemy()
	: Entity()
	, Collidable()
	, mPosition(0.0f, 0.0f)
	, mCenterPoint(0.0f, 0.0f)
	, mTargetPoint(0.0f, 0.0f)
	, mTargetPosition(0.0f, 0.0f)
	, mEnemyRect(0, 0, 0, 0)
	, mTargetPointUpdate(0.0f)
	, mHealth(0)
	, mRemoveCollider(false)
	, mPlayer(nullptr)
	, mFacingDirection(0.0f, 1.0f)
{

}
Enemy::~Enemy()
{

}

void Enemy::LoadAnimations()
{
	// Load IDLE_UP animation
	Animation* idleUp = new Animation();
	idleUp->AddFrame("enemy_idle_up_1.png");
	idleUp->SetFrameDuration(0.2f);
	idleUp->SetLooping(true);
	mAnimationController.AddAnimation("idle_up", idleUp);

	// Load IDLE_DOWN animation
	Animation* idleDown = new Animation();
	idleDown->AddFrame("enemy_idle_down_1.png");
	idleDown->SetFrameDuration(0.2f);
	idleDown->SetLooping(true);
	mAnimationController.AddAnimation("idle_down", idleDown);

	// Load IDLE_LEFT animation
	Animation* idleLeft = new Animation();
	idleLeft->AddFrame("enemy_idle_left_1.png");
	idleLeft->SetFrameDuration(0.2f);
	idleLeft->SetLooping(true);
	mAnimationController.AddAnimation("idle_left", idleLeft);

	// Load IDLE_RIGHT animation
	Animation* idleRight = new Animation();
	idleRight->AddFrame("enemy_idle_right_1.png");
	idleRight->SetFrameDuration(0.2f);
	idleRight->SetLooping(true);
	mAnimationController.AddAnimation("idle_right", idleRight);

	// Load WALK_UP animation
	Animation* walkUp = new Animation();
	walkUp->AddFrame("enemy_walk_up_1.png");
	walkUp->AddFrame("enemy_walk_up_2.png");
	walkUp->AddFrame("enemy_walk_up_3.png");
	walkUp->AddFrame("enemy_walk_up_4.png");
	walkUp->AddFrame("enemy_walk_up_5.png");
	walkUp->AddFrame("enemy_walk_up_6.png");
	walkUp->AddFrame("enemy_walk_up_7.png");
	walkUp->AddFrame("enemy_walk_up_8.png");
	walkUp->AddFrame("enemy_walk_up_9.png");
	walkUp->AddFrame("enemy_walk_up_10.png");
	walkUp->SetFrameDuration(0.30f);
	walkUp->SetLooping(true);
	mAnimationController.AddAnimation("walk_up", walkUp);

	// Load WALK_DOWN animation
	Animation* walkDown = new Animation();
	walkDown->AddFrame("enemy_walk_down_1.png");
	walkDown->AddFrame("enemy_walk_down_2.png");
	walkDown->AddFrame("enemy_walk_down_3.png");
	walkDown->AddFrame("enemy_walk_down_4.png");
	walkDown->AddFrame("enemy_walk_down_5.png");
	walkDown->AddFrame("enemy_walk_down_6.png");
	walkDown->AddFrame("enemy_walk_down_7.png");
	walkDown->AddFrame("enemy_walk_down_8.png");
	walkDown->AddFrame("enemy_walk_down_9.png");
	walkDown->AddFrame("enemy_walk_down_10.png");
	walkDown->SetFrameDuration(0.30f);
	walkDown->SetLooping(true);
	mAnimationController.AddAnimation("walk_down", walkDown);

	// Load WALK_LEFT animation
	Animation* walkLeft = new Animation();
	walkLeft->AddFrame("enemy_walk_left_1.png");
	walkLeft->AddFrame("enemy_walk_left_2.png");
	walkLeft->AddFrame("enemy_walk_left_3.png");
	walkLeft->AddFrame("enemy_walk_left_4.png");
	walkLeft->AddFrame("enemy_walk_left_5.png");
	walkLeft->AddFrame("enemy_walk_left_6.png");
	walkLeft->AddFrame("enemy_walk_left_7.png");
	walkLeft->AddFrame("enemy_walk_left_8.png");
	walkLeft->AddFrame("enemy_walk_left_9.png");
	walkLeft->AddFrame("enemy_walk_left_10.png");
	walkLeft->SetFrameDuration(0.30f);
	walkLeft->SetLooping(true);
	mAnimationController.AddAnimation("walk_left", walkLeft);

	// Load WALK_RIGHT animation
	Animation* walkRight = new Animation();
	walkRight->AddFrame("enemy_walk_right_1.png");
	walkRight->AddFrame("enemy_walk_right_2.png");
	walkRight->AddFrame("enemy_walk_right_3.png");
	walkRight->AddFrame("enemy_walk_right_4.png");
	walkRight->AddFrame("enemy_walk_right_5.png");
	walkRight->AddFrame("enemy_walk_right_6.png");
	walkRight->AddFrame("enemy_walk_right_7.png");
	walkRight->AddFrame("enemy_walk_right_8.png");
	walkRight->AddFrame("enemy_walk_right_9.png");
	walkRight->AddFrame("enemy_walk_right_10.png");
	walkRight->SetFrameDuration(0.30f);
	walkRight->SetLooping(true);
	mAnimationController.AddAnimation("walk_right", walkRight);

	// Set initial animation
	mAnimationController.SetCurrentAnimation("idle_down");
}

void Enemy::Load()
{
	LoadAnimations();

	mTargetPointUpdate = 0.0f;
	mRemoveCollider = false;

	float halfWidth = 25.0f;  
	float halfHeight = 25.0f;

	// HARDCODED ENEMY SIZE ; was having problems getting sprite size with 
	/*float halfWidth = X::GetSpriteWidth(firstAnim->GetCurrentFrame()) * 0.5f;
	float halfHeight = X::GetSpriteHeight(firstAnim->GetCurrentFrame()) * 0.5f;*/

	mEnemyRect.min.x = -halfWidth / 2;
	mEnemyRect.max.x = halfWidth / 2;
	mEnemyRect.min.y = -halfHeight / 2;
	mEnemyRect.max.y = halfHeight ;

	mFacingDirection = X::Math::Vector2(0.0f, 1.0f);
}

void Enemy::Update(float deltaTime)
{
	if (mRemoveCollider)
	{
		CollisionManager::Get()->RemoveCollidable(this);
		mRemoveCollider = false;
	}

	if (!IsActive())
	{
		return;
	}

	const float speed = 70.0f;
	bool isMoving = false;

	// Chase the player 
	if (mPlayer != nullptr)
	{
		mTargetPoint = mPlayer->GetPosition();
	}

	X::Math::Vector2 direction = X::Math::Normalize(mTargetPoint - mPosition);
	if (X::Math::Vector2::SqrMagnitude(direction) > 0.0f)
	{
		mFacingDirection = direction;
		isMoving = true;

		X::Math::Vector2 displacement = direction * speed * deltaTime;
		X::Math::Vector2 maxDisplacement = displacement;
		X::Math::Rect currentRect = mEnemyRect;
		currentRect.min += mPosition;
		currentRect.max += mPosition;
		if (TileMap::Get()->HasCollision(currentRect, maxDisplacement, displacement))
		{
			mPosition += displacement;
		}
		else
		{
			mPosition += displacement;
		}
		currentRect = mEnemyRect;
		currentRect.min += mPosition;
		currentRect.max += mPosition;
		SetRect(currentRect);
	}
	UpdateAnimation(isMoving);
	mAnimationController.Update(deltaTime);
}

void Enemy::UpdateAnimation(bool isMoving)
{
	float absX = abs(mFacingDirection.x);
	float absY = abs(mFacingDirection.y);

	std::string animationName;

	if (isMoving)
	{
		// Walking animations
		if (absX > absY)
		{
			animationName = (mFacingDirection.x > 0) ? "walk_right" : "walk_left";
		}
		else
		{
			animationName = (mFacingDirection.y > 0) ? "walk_down" : "walk_up";
		}
	}
	else
	{
		// Idle animations
		if (absX > absY)
		{
			animationName = (mFacingDirection.x > 0) ? "idle_right" : "idle_left";
		}
		else
		{
			animationName = (mFacingDirection.y > 0) ? "idle_down" : "idle_up";
		}
	}

	mAnimationController.SetCurrentAnimation(animationName);
}

void Enemy::Render()
{
	if (IsActive())
	{
		mAnimationController.Render(mPosition);
	}
}

void Enemy::Unload()
{

}

int Enemy::GetType() const
{
	return (IsActive()) ? ET_ENEMY : ET_NONE;
}
const X::Math::Vector2& Enemy::GetPosition() const
{
	return mPosition;
}

void Enemy::OnCollision(Collidable* collidable)
{
	if (IsActive())
	{
		if (collidable->GetType() == ET_PLAYER)
		{
			mHealth = 0;
			mRemoveCollider = true;
		}
		else if (collidable->GetType() == ET_BULLET)
		{
			mHealth = 0;
			mRemoveCollider = true;
		}
	}
}

bool Enemy::IsActive() const
{
	return mHealth > 0;
}
void Enemy::SetActive(const X::Math::Vector2& position, int health)
{
	mPosition = position;
	mCenterPoint = position;
	mTargetPoint = position;
	mTargetPointUpdate = 0.0f;
	mHealth = health;

	X::Math::Rect currentRect = mEnemyRect;
	currentRect.min += position;
	currentRect.max += position;

	SetRect(currentRect);
	SetCollisionFilter(ET_PLAYER | ET_BULLET);

	CollisionManager::Get()->AddCollidable(this);
	mRemoveCollider = false;
}
void Enemy::SetPlayer(Player* player)
{
	mPlayer = player;
}

void Enemy::SetInactive()
{
	// Only remove from collision if currently active
	if (IsActive())
	{
		CollisionManager::Get()->RemoveCollidable(this);
	}

	mHealth = 0;
	mRemoveCollider = false;
}