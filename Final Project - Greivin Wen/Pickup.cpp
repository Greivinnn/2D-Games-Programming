#include "Pickup.h"
#include "CollisionManager.h"

Pickup::Pickup()
    : Entity(), Collidable(), mImageID(0), mPosition(0.0f, 0.0f), mIsActive(false), mRemoveCollider(false)
{

}
Pickup::~Pickup()
{

}

void Pickup::Load()
{
    mImageID = X::LoadTexture("ammo-pistol.png");
    mIsActive = false;
    mRemoveCollider = false;
}

void Pickup::Update(float deltaTime)
{
    if (mRemoveCollider == true)
    {
        CollisionManager::Get()->RemoveCollidable(this);
        mRemoveCollider = false;
    }
}

void Pickup::Render()
{
    if (mIsActive == true)
    {
        X::DrawSprite(mImageID, mPosition);
    }
}

void Pickup::Unload()
{

}

int Pickup::GetType() const
{
    return mIsActive ? ET_PICKUP : 0;
}

void Pickup::OnCollision(Collidable* collidable)
{
    if (mIsActive == true)
    {
        mIsActive = false;
        mRemoveCollider = true;
    }
}

const X::Math::Vector2& Pickup::GetPosition() const
{
    return mPosition;
}

bool Pickup::IsActive() const
{
    return mIsActive;
}

void Pickup::SetActive(const X::Math::Vector2& position)
{
    mIsActive = true;
    mPosition = position;
    float halfWidth = X::GetSpriteWidth(mImageID) * 0.5f;
    float halfHeight = X::GetSpriteHeight(mImageID) * 0.5f;
    X::Math::Rect newRect;
    newRect.left = position.x - halfWidth;
    newRect.right = position.x + halfWidth;
    newRect.top = position.y - halfHeight;
    newRect.bottom = position.y + halfHeight;

    SetRect(newRect);
    SetCollisionFilter(ET_PLAYER);
    CollisionManager::Get()->AddCollidable(this);
}

void Pickup::SetInactive()
{
    if (mIsActive)
    {
        CollisionManager::Get()->RemoveCollidable(this);
    }
    
    mIsActive = false;
    mRemoveCollider = false;
}