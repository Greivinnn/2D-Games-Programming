#include <XEngine.h>
#include "Ship.h"
#include "StartState.h"
#include "RunGameState.h"
#include "EndState.h"

State gActiveState = State::Start;
GameState* gCurrentState = nullptr;
std::map<State, GameState*> gGameStates;

void GameInit()
{
	gGameStates[State::Start] = new StartState();
	gGameStates[State::RunGame] = new RunGameState();
	gGameStates[State::End] = new EndState();
	gActiveState = State::Start;

	gCurrentState = gGameStates[gActiveState];
	gCurrentState->Load();
}

void GameRender()
{
	
}

bool GameLoop(float deltaTime)
{
	State newState = gGameStates[gActiveState]->Update(deltaTime);
	gCurrentState->Render();
	if (newState != gActiveState)
	{
		gCurrentState->Unload();
		gCurrentState = gGameStates[newState];
		gCurrentState->Load();
		gActiveState = newState;
	}
	
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	gCurrentState->Unload();
	for (auto& state : gGameStates)
	{
		delete state.second;
	}
	gGameStates.clear();
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
