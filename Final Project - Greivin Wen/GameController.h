#pragma once
#include "Entity.h"
#include "Player.h"
#include "BulletPool.h"  
#include "Enum.h"

class GameController : public Entity
{
public:
    ~GameController();
    static GameController* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void ChangeState(State newState);
    State GetCurrentState() const;

private:
    GameController();
    static GameController* mInstance;

    Player mPlayer;
    BulletPool mBulletPool;  
    State mCurrentState;
    X::TextureId mTitleScreen;

    void UpdateStartScreen(float deltaTime);
    void UpdateRunGame(float deltaTime);
    void UpdateEndScreen(float deltaTime);

    void RenderStartScreen();
    void RenderRunGame();
    void RenderEndScreen();
};