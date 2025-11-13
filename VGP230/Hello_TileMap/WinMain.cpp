#include <XEngine.h>
#include "TileMap.h"

// g is for gloabal
// c is for const 
// s is for static
TileMap gTileMap;

std::vector<int> gTiles = {
	0, 0, 0, 0, 0, 0, 3, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 1, 0, 0, 0, 2, 2, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1
};

void GameInit()
{
	gTileMap.Load();
	gTileMap.LoadMap(gTiles, 10, 32.0f);
}

void GameRender()
{
	gTileMap.Render();
}

bool GameUpdate(float deltaTime)
{
	gTileMap.Update(deltaTime);
	GameRender();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	gTileMap.Unload();
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
