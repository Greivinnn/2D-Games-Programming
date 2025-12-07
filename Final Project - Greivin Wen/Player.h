#pragma once
#include "Entity.h"
#include "Collidable.h"
#include "FSMController.h"

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

    // player functions
    void SetVelocity(const X::Math::Vector2& velocity);
	const X::Math::Vector2& GetVelocity() const;
	void SetPosition(const X::Math::Vector2& position);
private:
    X::TextureId mImageID;
    X::Math::Vector2 mPosition;
	X::Math::Vector2 mVelocity;
    X::Math::Vector2 mFacingDirection;
    X::Math::Rect mPlayerRect;

    int mHealth;
    bool mRemoveCollider;

    FSMController mStateMachine;
};