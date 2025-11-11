#include "RunGameState.h"
#include <XEngine.h>
#include "Game.h"

RunGameState::RunGameState()
	:GameState(State::RunGame)
	, mGame(nullptr)
	, mSoundId(0)
	, mStartPlaying(false)
{
}

RunGameState::~RunGameState()
{
}

void RunGameState::Load()
{
	mGame = new Game();
	mGame->Load();
	mSoundId = X::LoadSound("RunStateMusic.wav");
	mStartPlaying = true;
}

State RunGameState::Update(float deltaTime)
{
	PlaySong();
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
		mStartPlaying = false;
		PlaySong();
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

void RunGameState::PlaySong()
{
	if (mStartPlaying)
	{
		X::PlaySoundLoop(mSoundId);
	}
	else
	{
		X::StopSoundLoop(mSoundId);
	}
}
