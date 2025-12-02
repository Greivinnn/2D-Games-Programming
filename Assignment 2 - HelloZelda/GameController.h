#pragma once
#include "Entity.h"
#include "Player.h"
#include "BulletPool.h"  

class GameController : public Entity
{
public:
    ~GameController();
    static GameController* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

private:
    GameController();
    static GameController* mInstance;

    Player mPlayer;
    BulletPool mBulletPool;  
};