#include "Player.h"
#include "CollisionManager.h"
#include "TileMap.h"
#include "Bullet.h"
#include "BulletPool.h"

Player::Player()
    : Entity()
    , Collidable()
    , mImageID(0)
    , mPosition(0.0f, 0.0f)
    , mHealth(10)
    , mRemoveCollider(false)
    , mBulletPool(nullptr)
    , mDamageCooldown(0.0f)
    , mShootCooldown(0.0f)
	, mCurrentAmmo(0)
	, mMaxAmmo(20)
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
    SetCollisionFilter(ET_ENEMY | ET_PICKUP);
    mRemoveCollider = false;
    CollisionManager::Get()->AddCollidable(this);

    mDamageCooldown = 0.0f;
    mShootCooldown = 0.0f;
    mCurrentAmmo = 10;
}

void Player::Update(float deltaTime)
{
    if (mDamageCooldown > 0.0f)
    {
        mDamageCooldown -= deltaTime;
    }

    if (mShootCooldown > 0.0f)
    {
        mShootCooldown -= deltaTime;
    }

    if (mHealth <= 0)
    {
        if (mRemoveCollider == true)
        {
            CollisionManager::Get()->RemoveCollidable(this);
            mRemoveCollider = false;
        }
        return;
    }

    // Movement
    const float speed = 200.0f;
    X::Math::Vector2 direction = X::Math::Vector2::Zero();

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
        X::Math::Vector2 maxDisplacement = direction * speed * deltaTime;
        X::Math::Vector2 displacement = maxDisplacement;

        X::Math::Rect currentRect = mPlayerRect;
        currentRect.min += mPosition;
        currentRect.max += mPosition;

        TileMap::Get()->HasCollision(currentRect, maxDisplacement, displacement);
        mPosition += displacement;

        currentRect = mPlayerRect;
        currentRect.min += mPosition;
        currentRect.max += mPosition;
        SetRect(currentRect);
    }

    // Shooting 
    if (X::IsMouseDown(X::Mouse::LBUTTON) && mShootCooldown <= 0.0f && mBulletPool != nullptr && mCurrentAmmo > 0)
    {
        // Get mouse position in world space
        float mouseX = X::GetMouseScreenX();
        float mouseY = X::GetMouseScreenY();

        X::Math::Vector2 mousePos(mouseX, mouseY);

        // Calculate direction from player to mouse
        X::Math::Vector2 shootDirection = mousePos - mPosition;

        if (X::Math::MagnitudeSqr(shootDirection) > 0.0f)
        {
            shootDirection = X::Math::Normalize(shootDirection);

            // Calculate rotation angle (in radians)
            float rotation = atan2(shootDirection.y, shootDirection.x);
            rotation += X::Math::kPiByTwo;

            // Spawn bullet slightly in front of player
            const float spawnOffset = 30.0f;
            X::Math::Vector2 spawnPos = mPosition + (shootDirection * spawnOffset);

            Bullet* bullet = mBulletPool->GetBullet();
            bullet->SetEntityType(ET_PLAYER);
            bullet->SetActive(spawnPos, rotation, 0.5f);

            mShootCooldown = 0.2f;
            mCurrentAmmo--;
        }
    }
}

void Player::Render()
{
    if (mHealth > 0)
    {
        X::DrawSprite(mImageID, mPosition);
        char buffer[128];
        sprintf_s(buffer, "Player Health: %d | Ammo: %d/%d", mHealth, mCurrentAmmo, mMaxAmmo);

        float textWidth = X::GetTextWidth(buffer, 24.0f);
        float centerX = (1280.0f - textWidth) * 0.075;
        X::DrawScreenText(buffer, centerX, 30.0f, 18.0f, X::Colors::White);
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
    if (mHealth <= 0)
    {
        return;
    }

    if (collidable->GetType() == ET_ENEMY)
    {
        if (mDamageCooldown <= 0.0f) 
        {
            mHealth -= 1;
            mDamageCooldown = 1.0f;  
        }
    }
    else if (collidable->GetType() == ET_PICKUP)
    {
        AddAmmo(5);
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

void Player::SetBulletPool(BulletPool* bulletPool)
{
    mBulletPool = bulletPool;
}

void Player::AddAmmo(int amount)
{
    mCurrentAmmo += amount;
    mCurrentAmmo = X::Math::Clamp(mCurrentAmmo, 0, mMaxAmmo);
}

int Player::GetCurrentAmmo() const
{
    return mCurrentAmmo;
}