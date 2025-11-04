#include "RunGameState.h"
#include <XEngine.h>
#include "Game.h"

RunGameState::RunGameState()
	:GameState(State::RunGame)
	, mGame(nullptr)
{
}

RunGameState::~RunGameState()
{
}

void RunGameState::Load()
{
	mGame = new Game();
	mGame->Load();
}

State RunGameState::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ESCAPE))
	{
		return State::Start;
	}

	if (mGame)
	{
		mGame->Update(deltaTime);
	}

	if (mGame && mGame->IsGameOver())
	{
		return State::End;
	}

	return State::RunGame;
}

void RunGameState::Render()
{
	if(mGame)
	{
		mGame->Render();
	}
	//const float textSize = 100.0f;
	//const char* text = "<\n\nRUNGAME STATE REACH>";
	//float textWidth = X::GetTextWidth(text, textSize);
	//float screenX = (X::GetScreenWidth() - textWidth) * 0.5f;
	//float screenY = (X::GetScreenHeight() - textWidth) * 0.5f;
	/*X::DrawScreenText(text, screenX, screenY, textSize, X::Colors::Green);*/
}

void RunGameState::Unload()
{
	if (mGame)
	{
		mGame->Unload();
		delete mGame;
		mGame = nullptr;
	}
}
