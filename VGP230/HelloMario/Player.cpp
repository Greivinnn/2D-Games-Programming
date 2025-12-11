#include "Player.h"
#include "CollisionManager.h"
#include "TileMap.h"
#include "States.h"
#include "ProjectileManager.h"

Player::Player()
    : Entity(), Collidable(), mImageID(0), mPosition(0.0f, 0.0f), mHealth(100), mRemoveCollider(false), mFacingDirection(1.0f, 0.0f)
{

}

Player::~Player()
{

}

void Player::Load()
{
    mImageID = X::LoadTexture("mushroom.png");

    

    float halfWidth = X::GetSpriteWidth(mImageID) * 0.5f;
    float halfHeight = X::GetSpriteHeight(mImageID) * 0.5f;
    mPlayerRect.left = -halfWidth;
    mPlayerRect.right = halfWidth;
    mPlayerRect.top = -halfHeight;
    mPlayerRect.bottom = halfHeight;

    const Tile* safeTile = TileMap::Get()->GetFirstWalkableTile();
    SetPosition(safeTile->GetPosition());

    SetCollisionFilter(ET_ENEMY || ET_PICKUP);
    mRemoveCollider = false;
    CollisionManager::Get()->AddCollidable(this);

    mStateMachine.CleanUp();
    mStateMachine.AddState(MS_IDLE, new IdleState(this));
    mStateMachine.AddState(MS_WALK, new WalkState(this));
    mStateMachine.AddState(MS_JUMP, new JumpState(this));
    mStateMachine.AddState(MS_FALL, new FallState(this));
    mStateMachine.SetState(MS_FALL);
}

void Player::Update(float deltaTime)
{
    if (mHealth <= 0)
    {
        if (mRemoveCollider == true)
        {
            CollisionManager::Get()->RemoveCollidable(this);
            mRemoveCollider = false;
        }

        return;
    }

    mStateMachine.Update(deltaTime);
    if (X::IsKeyDown(X::Keys::D))
    {
        mFacingDirection.x = 1.0f;
    }
    else if (X::IsKeyDown(X::Keys::A))
    {
        mFacingDirection.x = -1.0f;
    }

    if (X::IsKeyPressed(X::Keys::SPACE))
    {
        Projectile* projectile = ProjectileManager::Get()->GetProjectile();
        projectile->SetActive(mPosition, mFacingDirection, 3.0f);
        projectile->SetEntityType(ET_PLAYER_PROJECTILE);
        projectile->SetFlip(mFacingDirection.x < 0.0f ? X::Flip::Horizontal : X::Flip::None);
    }
}

void Player::Render()
{
    if (mHealth > 0.0f)
    {
        X::DrawSprite(mImageID, mPosition);
    }
}

void Player::Unload()
{

}

int Player::GetType() const
{
    return ET_PLAYER;
}

void Player::SetPosition(const X::Math::Vector2& position)
{
	mPosition = position;
    X::Math::Rect currentRect = mPlayerRect;
    currentRect.min += position;
    currentRect.max += position;
    SetRect(currentRect);
}

void Player::OnCollision(Collidable* collidable)
{
    // DO NOTE REMOVE COLLIDABLES DURING THIS FUNCTION (WILL CRASH)

    if (mHealth <= 0)
    {
        return;
    }

    if (collidable->GetType() == ET_ENEMY)
    {
        mHealth -= 10;
    }
    else if (collidable->GetType() == ET_ENEMY)
    {
        mHealth += 20;
    }

    mHealth = X::Math::Clamp(mHealth, 0, 100);

    if (mHealth <= 0)
    {
        mRemoveCollider = true;
    }
}

const X::Math::Vector2& Player::GetPosition() const
{
    return mPosition;
}

void Player::SetVelocity(const X::Math::Vector2& velocity)
{
	mVelocity = velocity;
}

const X::Math::Vector2& Player::GetVelocity() const
{
	return mVelocity;
}
