#include <XEngine.h>
#include "Ship.h"

Ship mShip;

void GameInit()
{
	mShip.Load();
}

void GameRender()
{
	
}

bool GameLoop(float deltaTime)
{
	mShip.Update(deltaTime);
	mShip.Render();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	mShip.Unload();
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// main function 
	
	X::Start("xconfig.json");
	// X::Start(): Initializes the XEngine using the configuration file (xconfig.json)
	
	GameInit();
	// GameInit(): Loads textures and setups variables

	X::Run(GameLoop);
	// X::RUN(GameLoop): Starts the main loop, repeatedly calling GameLoop every frame

	GameCleanup();
	// GameCleanup(): Called when the loop ends (in this case when you press ESC)

	X::Stop();
	// X:Stop(): Shuts down the engine properly

	return 0;
}
