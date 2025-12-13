#pragma once
#include "Pickup.h"

class PickupManager : public Entity
{
public:
    ~PickupManager();
    static PickupManager* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void SpawnPickup(int count);
    void Reset();
private:
    PickupManager();
    static PickupManager* mInstance;

    std::vector<Pickup*> mPickups;
    int mNextAvailableIndex;

    // Auto spawn system
    float mSpawnTimer;
    float mSpawnInterval;
    int mMaxActivePickups;

    int GetActivePickupCount() const;
};