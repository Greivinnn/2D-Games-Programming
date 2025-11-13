#include <XEngine.h>
#include "TileMap.h"

void GameInit()
{
	TileMap::Get()->Load();
}

void GameRender()
{
	TileMap::Get()->Render();
}

bool GameUpdate(float deltaTime)
{
	TileMap::Get()->Update(deltaTime);
	GameRender();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// main function 

	X::Start("xconfig.json");
	// X::Start(): Initializes the XEngine using the configuration file (xconfig.json)

	GameInit();
	// GameInit(): Loads textures and setups variables

	X::Run(GameUpdate);
	// X::RUN(GameLoop): Starts the main loop, repeatedly calling GameLoop every frame

	GameCleanup();
	// GameCleanup(): Called when the loop ends (in this case when you press ESC)

	X::Stop();
	// X:Stop(): Shuts down the engine properly

	return 0;
}
