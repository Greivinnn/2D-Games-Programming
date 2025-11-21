#pragma once
#include "Entity.h"

class Collidable;

class CollisionManager : public Entity
{
public:
    ~CollisionManager();
    static CollisionManager* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void AddCollidable(Collidable* collidable);
    void RemoveCollidable(Collidable* collidable);

private:
    CollisionManager();
    static CollisionManager* mInstance;

    std::vector<Collidable*> mCollidables;
    bool mShowCollidables;
};