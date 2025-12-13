#pragma once
#include "Entity.h"
#include "Collidable.h"
#include "AnimationController.h"

class BulletPool;

class Player : public Entity, public Collidable
{
public:
    Player();
    ~Player();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    int GetType() const override;
    void OnCollision(Collidable* collidable) override;
    const X::Math::Vector2& GetPosition() const override;

    void SetBulletPool(BulletPool* bulletPool);

	void AddAmmo(int amount);   
	int GetCurrentAmmo() const;

    bool IsDead() const;
    void Reset();

private:
    X::TextureId mImageID;
    X::Math::Vector2 mPosition;
    X::Math::Rect mPlayerRect;

    int mHealth;
    bool mRemoveCollider;
    BulletPool* mBulletPool;
    float mDamageCooldown;
    float mShootCooldown;
	int mCurrentAmmo;
	int mMaxAmmo;

    float mIdleTimer;
    const float mMaxIdleTime;
    X::Math::Vector2 mLastPosition;
    bool mIsIdle;
    float mThunderCooldown;
    X::Math::Vector2 mSpawnPosition;

    // Animation
    AnimationController mAnimationController;
    X::Math::Vector2 mFacingDirection;
    bool mIsShooting;

    //Heart UI
    X::TextureId mHeartFullTexture;
    X::TextureId mHeartEmptyTexture;

    // Lightning animation
    Animation* mLightningAnimation;
    bool mShowLightning;
    float mLightningTimer;

	//Helper functions
    void LoadAnimations();
    void UpdateAnimation(bool isMoving, bool isShooting);
	void RenderHealth() const;  
};