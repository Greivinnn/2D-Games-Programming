#include "Pickup.h"
#include "CollisionManager.h"

Pickup::Pickup()
    : Entity()
    , Collidable()
    , mAmmoImageId(0)
    , mPosition(0.0f, 0.0f)
    , mIsActive(false)
    , mRemoveCollider(false)
	, mPickupType(PickupType::Ammo)
	, mHealthImageId(0)
{

}
Pickup::~Pickup()
{

}

void Pickup::Load()
{
    mAmmoImageId = X::LoadTexture("ammo-pistol.png");
	mHealthImageId = X::LoadTexture("HeartFull.png");
    mIsActive = false;
    mRemoveCollider = false;
	mPickupType = PickupType::Ammo;
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
        X::TextureId textureToRender = (mPickupType == PickupType::Health) ? mHealthImageId : mAmmoImageId;
        X::DrawSprite(textureToRender, mPosition);
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

void Pickup::SetActive(const X::Math::Vector2& position, PickupType type)
{
    mIsActive = true;
    mPosition = position;
    mPickupType = type;

    X::TextureId textureToUse = (type == PickupType::Health) ? mHealthImageId : mAmmoImageId;
    float halfWidth = X::GetSpriteWidth(textureToUse) * 0.5f;
    float halfHeight = X::GetSpriteHeight(textureToUse) * 0.5f;

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

PickupType Pickup::GetPickupType() const
{
    return mPickupType;
}