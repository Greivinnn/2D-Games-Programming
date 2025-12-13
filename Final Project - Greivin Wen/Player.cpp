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
    , mHealth(3)
    , mRemoveCollider(false)
    , mBulletPool(nullptr)
    , mDamageCooldown(0.0f)
    , mShootCooldown(0.0f)
    , mCurrentAmmo(0)
    , mMaxAmmo(20)
    , mIdleTimer(0.0f)
    , mMaxIdleTime(3.0f)
    , mLastPosition(0.0f, 0.0f)
    , mIsIdle(false)
    , mThunderCooldown(0.0f)
    , mFacingDirection(0.0f, 1.0f)
    , mIsShooting(false)
    , mSpawnPosition(0.0f, 0.0f)
    , mLightningAnimation(nullptr)
    , mShowLightning(false)
    , mLightningTimer(0.0f)
    , mIsBlinking(false)
    , mBlinkTimer(0.0f)
    , mBlinkDuration(1.0f)
    , mBlinkInterval(0.1f)  
    , mIsVisible(true)
{
}

Player::~Player()
{
}

void Player::LoadAnimations()
{
    // Create and load IDLE_UP animation
    Animation* idleUp = new Animation();
    idleUp->AddFrame("player_idle_up_1.png");
    idleUp->SetFrameDuration(0.2f);
    idleUp->SetLooping(true);
    mAnimationController.AddAnimation("idle_up", idleUp);

    // Create and load IDLE_DOWN animation
    Animation* idleDown = new Animation();
    idleDown->AddFrame("player_idle_down_1.png");
    idleDown->SetFrameDuration(0.2f);
    idleDown->SetLooping(true);
    mAnimationController.AddAnimation("idle_down", idleDown);

    // Create and load IDLE_LEFT animation
    Animation* idleLeft = new Animation();
    idleLeft->AddFrame("player_idle_left_1.png");
    idleLeft->SetFrameDuration(0.2f);
    idleLeft->SetLooping(true);
    mAnimationController.AddAnimation("idle_left", idleLeft);

    // Create and load IDLE_RIGHT animation
    Animation* idleRight = new Animation();
    idleRight->AddFrame("player_idle_right_1.png");
    idleRight->SetFrameDuration(0.2f);
    idleRight->SetLooping(true);
    mAnimationController.AddAnimation("idle_right", idleRight);

    // Create and load WALK_UP animation
    Animation* walkUp = new Animation();
    walkUp->AddFrame("player_walk_up_1.png");
    walkUp->AddFrame("player_walk_up_2.png");
    walkUp->AddFrame("player_walk_up_3.png");
    walkUp->AddFrame("player_walk_up_4.png");
    walkUp->SetFrameDuration(0.15f);
    walkUp->SetLooping(true);
    mAnimationController.AddAnimation("walk_up", walkUp);

    // Create and load WALK_DOWN animation
    Animation* walkDown = new Animation();
    walkDown->AddFrame("player_walk_down_1.png");
    walkDown->AddFrame("player_walk_down_2.png");
    walkDown->AddFrame("player_walk_down_3.png");
    walkDown->AddFrame("player_walk_down_4.png");
    walkDown->SetFrameDuration(0.15f);
    walkDown->SetLooping(true);
    mAnimationController.AddAnimation("walk_down", walkDown);

    // Create and load WALK_LEFT animation
    Animation* walkLeft = new Animation();
    walkLeft->AddFrame("player_walk_left_1.png");
    walkLeft->AddFrame("player_walk_left_2.png");
    walkLeft->AddFrame("player_walk_left_3.png");
    walkLeft->AddFrame("player_walk_left_4.png");
    walkLeft->SetFrameDuration(0.15f);
    walkLeft->SetLooping(true);
    mAnimationController.AddAnimation("walk_left", walkLeft);

    // Create and load WALK_RIGHT animation
    Animation* walkRight = new Animation();
    walkRight->AddFrame("player_walk_right_1.png");
    walkRight->AddFrame("player_walk_right_2.png");
    walkRight->AddFrame("player_walk_right_3.png");
    walkRight->AddFrame("player_walk_right_4.png");
    walkRight->SetFrameDuration(0.15f);
    walkRight->SetLooping(true);
    mAnimationController.AddAnimation("walk_right", walkRight);

    Animation* shootUp = new Animation();
    shootUp->AddFrame("player_shoot_up_1.png");
    shootUp->AddFrame("player_shoot_up_2.png");
    shootUp->AddFrame("player_shoot_up_3.png");
    shootUp->AddFrame("player_shoot_up_4.png");
    shootUp->SetFrameDuration(0.1f);
    shootUp->SetLooping(false); 
    mAnimationController.AddAnimation("shoot_up", shootUp);

    // Create and load SHOOT_DOWN animation
    Animation* shootDown = new Animation();
    shootDown->AddFrame("player_shoot_down_1.png");
    shootDown->AddFrame("player_shoot_down_2.png");
    shootDown->AddFrame("player_shoot_down_3.png");
    shootDown->AddFrame("player_shoot_down_4.png");
    shootDown->SetFrameDuration(0.1f);
    shootDown->SetLooping(false);
    mAnimationController.AddAnimation("shoot_down", shootDown);

    // Create and load SHOOT_LEFT animation
    Animation* shootLeft = new Animation();
    shootLeft->AddFrame("player_shoot_left_1.png");
    shootLeft->AddFrame("player_shoot_left_2.png");
    shootLeft->AddFrame("player_shoot_left_3.png");
    shootLeft->AddFrame("player_shoot_left_4.png");
    shootLeft->SetFrameDuration(0.1f);
    shootLeft->SetLooping(false);
    mAnimationController.AddAnimation("shoot_left", shootLeft);

    // Create and load SHOOT_RIGHT animation
    Animation* shootRight = new Animation();
    shootRight->AddFrame("player_shoot_right_1.png");
    shootRight->AddFrame("player_shoot_right_2.png");
    shootRight->AddFrame("player_shoot_right_3.png");
    shootRight->AddFrame("player_shoot_right_4.png");
    shootRight->SetFrameDuration(0.1f);
    shootRight->SetLooping(false);
    mAnimationController.AddAnimation("shoot_right", shootRight);


    // Set initial animation
    mAnimationController.SetCurrentAnimation("idle_down");
}

void Player::Reset()
{
    // Reset position to spawn point
    mPosition = mSpawnPosition;

    // Reset health to starting value
    mHealth = 3;

    // Reset ammo
    mCurrentAmmo = 10;

    // Reset cooldowns
    mDamageCooldown = 0.0f;
    mShootCooldown = 0.0f;
    mThunderCooldown = 0.0f;

    // Reset idle tracking
    mIdleTimer = 0.0f;
    mLastPosition = mPosition;
    mIsIdle = false;

    // Reset facing direction
    mFacingDirection = X::Math::Vector2(0.0f, 1.0f);
    mIsShooting = false;

    // Reset lightning animation
    mShowLightning = false;
    if (mLightningAnimation != nullptr)
    {
        mLightningAnimation->Reset();
    }

    mIsBlinking = false;
    mBlinkTimer = 0.0f;
    mIsVisible = true;

    // Re-enable collider if it was removed
    if (mRemoveCollider == true)
    {
        mRemoveCollider = false;
        CollisionManager::Get()->AddCollidable(this);
    }

    // Update collision rect
    X::Math::Rect currentRect = mPlayerRect;
    currentRect.min += mPosition;
    currentRect.max += mPosition;
    SetRect(currentRect);

    // Reset animation to idle
    mAnimationController.SetCurrentAnimation("idle_down");
}

void Player::Load()
{
    LoadAnimations();

    mHeartFullTexture = X::LoadTexture("HeartFull.png");
    mHeartEmptyTexture = X::LoadTexture("HeartEmpty.png");

    // Load lightning strike animation
    mLightningAnimation = new Animation();
    mLightningAnimation->AddFrame("Lightning_1.png");
    mLightningAnimation->AddFrame("Lightning_2.png");
    mLightningAnimation->AddFrame("Lightning_3.png");
    mLightningAnimation->AddFrame("Lightning_4.png");
    mLightningAnimation->AddFrame("Lightning_5.png");
    mLightningAnimation->AddFrame("Lightning_6.png");
    mLightningAnimation->AddFrame("Lightning_7.png");
    mLightningAnimation->AddFrame("Lightning_8.png");
    mLightningAnimation->SetFrameDuration(0.08f);  
    mLightningAnimation->SetLooping(false);

    mShowLightning = false;
    mLightningTimer = 0.0f;

    const Tile* safeTile = TileMap::Get()->GetFirstWalkableTile();
    mPosition = safeTile->GetPosition();
    mSpawnPosition = mPosition;

    Animation* firstAnim = mAnimationController.GetAnimation("idle_down");
    if (firstAnim != nullptr)
    {
        float halfWidth = X::GetSpriteWidth(firstAnim->GetCurrentFrame()) * 0.5f;
        float halfHeight = X::GetSpriteHeight(firstAnim->GetCurrentFrame()) * 0.5f;
        mPlayerRect.left = -halfWidth / 2;
        mPlayerRect.right = halfWidth / 2;
        mPlayerRect.top = -halfHeight / 2;
        mPlayerRect.bottom = halfHeight;
    }

    SetRect(mPlayerRect);
    SetCollisionFilter(ET_ENEMY | ET_PICKUP);
    mRemoveCollider = false;
    CollisionManager::Get()->AddCollidable(this);

    mDamageCooldown = 0.0f;
    mShootCooldown = 0.0f;
    mCurrentAmmo = 10;

    mIdleTimer = 0.0f;
    mLastPosition = mPosition;
    mIsIdle = false;
    mThunderCooldown = 0.0f;
    mFacingDirection = X::Math::Vector2(0.0f, 1.0f);

    mIsBlinking = false;
    mBlinkTimer = 0.0f;
    mIsVisible = true;
}

void Player::UpdateAnimation(bool isMoving, bool isShooting)
{
    float absX = abs(mFacingDirection.x);
    float absY = abs(mFacingDirection.y);

    std::string animationName;

    // Priority 1: Shooting animation (highest priority)
    if (isShooting)
    {
        if (absX > absY)
        {
            animationName = (mFacingDirection.x > 0) ? "shoot_right" : "shoot_left";
        }
        else
        {
            animationName = (mFacingDirection.y > 0) ? "shoot_down" : "shoot_up";
        }
    }
    // Priority 2: Walking animation
    else if (isMoving)
    {
        if (absX > absY)
        {
            animationName = (mFacingDirection.x > 0) ? "walk_right" : "walk_left";
        }
        else
        {
            animationName = (mFacingDirection.y > 0) ? "walk_down" : "walk_up";
        }
    }
    // Priority 3: Idle animation
    else
    {
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

void Player::TriggerDamageEffect()
{
    mIsBlinking = true;
    mBlinkTimer = 0.0f;
    mIsVisible = true;
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

    if (mThunderCooldown > 0.0f)
    {
        mThunderCooldown -= deltaTime;
    }

    // Update lightning animation
    if (mShowLightning)
    {
        mLightningAnimation->Update(deltaTime);

        // Check if animation finished
        if (mLightningAnimation->IsFinished())
        {
            mShowLightning = false;
            mLightningAnimation->Reset();
        }
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

    if (mIsBlinking)
    {
        mBlinkTimer += deltaTime;

        int toggleCount = (int)(mBlinkTimer / mBlinkInterval);
        mIsVisible = (toggleCount % 2 == 0);

        if (mBlinkTimer >= mBlinkDuration)
        {
            mIsBlinking = false;
            mIsVisible = true;
            mBlinkTimer = 0.0f;
        }
    }

    // Movement
    const float speed = 200.0f;
    X::Math::Vector2 direction = X::Math::Vector2::Zero();
    bool isMoving = false;

    if (X::IsKeyDown(X::Keys::W))
    {
        direction.y = -1.0f;
        isMoving = true;
    }
    else if (X::IsKeyDown(X::Keys::S))
    {
        direction.y = 1.0f;
        isMoving = true;
    }
    if (X::IsKeyDown(X::Keys::A))
    {
        direction.x = -1.0f;
        isMoving = true;
    }
    else if (X::IsKeyDown(X::Keys::D))
    {
        direction.x = 1.0f;
        isMoving = true;
    }

    if (X::Math::MagnitudeSqr(direction) > 0.0f)
    {
        direction = X::Math::Normalize(direction);
        mFacingDirection = direction;
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

    bool isShooting = false;

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

            mFacingDirection = shootDirection;

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
            isShooting = true;
        }
    }

    std::string currentAnim = mAnimationController.GetCurrentAnimationName();
    if (currentAnim.find("shoot") != std::string::npos)
    {
        Animation* shootAnim = mAnimationController.GetAnimation(currentAnim);
        if (shootAnim && !shootAnim->IsFinished())
        {
            isShooting = true;  // Keep showing shoot animation until it finishes
        }
    }

    UpdateAnimation(isMoving, isShooting);
    mAnimationController.Update(deltaTime);

    // Idle detection and thunder strike
    if (mHealth > 0)
    {
        // Check if player has moved
        float movementThreshold = 1.0f;
        X::Math::Vector2 movement = mPosition - mLastPosition;
        float movementSqr = X::Math::Vector2::SqrMagnitude(movement);
        float thresholdSqr = movementThreshold * movementThreshold;

        if (movementSqr < thresholdSqr)
        {
            // Player is idle
            mIdleTimer += deltaTime;
            mIsIdle = true;

            if (mIdleTimer >= mMaxIdleTime && mThunderCooldown <= 0.0f)  // Check cooldown
            {
                // Thunder strike
                mHealth -= 1;
                mDamageCooldown = 1.0f;
                mThunderCooldown = 3.0f;  // 3 second cooldown before next thunder
                mIdleTimer = 0.0f;  // Reset idle timer

				mShowLightning = true;
				mLightningAnimation->Reset();
				TriggerDamageEffect();
            }
        }
        else
        {
            // Player is moving, reset timer
            mIdleTimer = 0.0f;
            mIsIdle = false;
        }

        mLastPosition = mPosition;
    }
}

void Player::RenderHealth() const
{
    const int maxHearts = 3;
    const float heartSize = 32.0f;
    const float heartSpacing = 40.0f; 
    const float startX = 20.0f;       
    const float startY = 20.0f;       

    for (int i = 0; i < maxHearts; ++i)
    {
        float heartX = startX + (i * heartSpacing);
        float heartY = startY;

        X::Math::Vector2 heartPosition(heartX, heartY);

        if (i < mHealth)
        {
            X::DrawSprite(mHeartFullTexture, heartPosition);
        }
        else
        {
            X::DrawSprite(mHeartEmptyTexture, heartPosition);
        }
    }
}

void Player::Render()
{
    if (mHealth > 0)
    {
        if (mIsVisible)
        {
            mAnimationController.Render(mPosition);
        }

        // Render lightning strike on top of player if active
        if (mShowLightning)
        {
            X::DrawSprite(mLightningAnimation->GetCurrentFrame(), mPosition);
        }

        RenderHealth();

        char ammoBuffer[128];
        sprintf_s(ammoBuffer, "AMMO: %d/%d", mCurrentAmmo, mMaxAmmo);

        float fontSize = 48.0f;
        float textWidth = X::GetTextWidth(ammoBuffer, fontSize);
        float screenWidth = 1280.0f;
        float screenHeight = 720.0f;

        float ammoX = screenWidth - textWidth - 30.0f;
        float ammoY = screenHeight - fontSize - 20.0f;

        X::DrawScreenText(ammoBuffer, ammoX + 2.0f, ammoY + 2.0f, fontSize, X::Colors::Black);

        X::DrawScreenText(ammoBuffer, ammoX, ammoY, fontSize, X::Colors::White);

        if (mIsIdle && mIdleTimer > (mMaxIdleTime * 0.5f)) {
            char warningBuffer[128];
            float timeLeft = mMaxIdleTime - mIdleTimer;
            sprintf_s(warningBuffer, "MOVE! Thunder in %.1f seconds!", timeLeft);

            float fontSize = 36.0f;
            float warningWidth = X::GetTextWidth(warningBuffer, fontSize);
            float warningX = (1280.0f - warningWidth) * 0.5f;
            float warningY = (720.0f - fontSize) * 0.5f; 

            float blinkSpeed = 4.0f + (timeLeft < 2.0f ? 4.0f : 0.0f);
            if ((int)(mIdleTimer * blinkSpeed) % 2 == 0)
            {
                X::DrawScreenText(warningBuffer, warningX + 2.0f, warningY + 2.0f, fontSize, X::Colors::Black);
                X::DrawScreenText(warningBuffer, warningX, warningY, fontSize, X::Colors::Red);
            }
        }
    }
    else
    {
        RenderHealth();
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
			TriggerDamageEffect();
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

bool Player::IsDead() const
{
    return mHealth <= 0;
}

