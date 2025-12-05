#include "Player.h"
#include "CollisionManager.h"
#include "TileMap.h"

Player::Player()
    : Entity(), Collidable(), mImageID(0), mPosition(0.0f, 0.0f), mHealth(100), mRemoveCollider(false)
{

}

Player::~Player()
{

}

void Player::Load()
{
    mImageID = X::LoadTexture("mushroom.png");

    const Tile* safeTile = TileMap::Get()->GetFirstWalkableTile();
    mPosition = safeTile->GetPosition();

    float halfWidth = X::GetSpriteWidth(mImageID) * 0.5f;
    float halfHeight = X::GetSpriteHeight(mImageID) * 0.5f;
    mPlayerRect.left = -halfWidth;
    mPlayerRect.right = halfWidth;
    mPlayerRect.top = -halfHeight;
    mPlayerRect.bottom = halfHeight;

    SetRect(mPlayerRect);
    SetCollisionFilter(ET_ENEMY || ET_PICKUP);
    mRemoveCollider = false;
    CollisionManager::Get()->AddCollidable(this);
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

    const float speed = 200.0f;
    X::Math::Vector2 direction = X::Math::Vector2::Zero();
    X::Math::Vector2 displacement = X::Math::Vector2::Zero();

    if (X::IsKeyDown(X::Keys::W))
    {
        direction.y = -1.0f;
    }
    else if (X::IsKeyDown(X::Keys::S))
    {
        direction.y = 1.0f;
    }
    if (X::IsKeyDown(X::Keys::A))
    {
        direction.x = -1.0f;
    }
    else if (X::IsKeyDown(X::Keys::D))
    {
        direction.x = 1.0f;
    }

    if (X::Math::MagnitudeSqr(direction) > 0.0f)
    {
        direction = X::Math::Normalize(direction);
        displacement = direction * speed * deltaTime;
        X::Math::Vector2 maxDisplacement = displacement;
        X::Math::Rect currentRect = mPlayerRect;
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

        currentRect = mPlayerRect;
        currentRect.min += mPosition;
        currentRect.max += mPosition;
        SetRect(currentRect);
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
