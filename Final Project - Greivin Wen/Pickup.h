#pragma once
#include "Entity.h"
#include "Collidable.h"
#include "Enum.h"

class Pickup : public Entity, public Collidable
{
public:
    Pickup();
    ~Pickup();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    int GetType() const override;
    void OnCollision(Collidable* collidable) override;
    const X::Math::Vector2& GetPosition() const override;

    bool IsActive() const;
    void SetActive(const X::Math::Vector2& position, PickupType type);

    void SetInactive();

    PickupType GetPickupType() const;
private:
    X::TextureId mAmmoImageId;
	X::TextureId mHealthImageId;
    X::Math::Vector2 mPosition;
    PickupType mPickupType;

    bool mIsActive;
    bool mRemoveCollider;
};