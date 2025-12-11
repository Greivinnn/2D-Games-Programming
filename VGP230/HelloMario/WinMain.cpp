  #include <XEngine.h>
#include "GameController.h"

void GameInit()
{
    GameController::Get()->Load();
}

bool GameUpdate(float deltaTime)
{
    GameController::Get()->Update(deltaTime);
    GameController::Get()->Render();

    return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
    GameController::Get()->Unload();
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    X::Start("xconfig.json");
    GameInit();

    X::Run(GameUpdate);

    GameCleanup();
    X::Stop();

    return 0;
}