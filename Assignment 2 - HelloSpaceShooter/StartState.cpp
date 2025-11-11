#include "StartState.h"
#include <XEngine.h>

StartState::StartState()
	:GameState(State::Start)
	, mBackgroundId(0)
	, mSoundId(0)
	, mSoundId2(0)
	, mStartPlaying(false)
{
}

StartState::~StartState()
{
}

void StartState::Load()
{
	mBackgroundId = X::LoadTexture("StartBackground.png");
	mSoundId = X::LoadSound("StartingScreenMusic.wav");
	mSoundId2 = X::LoadSound("game-start.wav");
	mStartPlaying = true;
}

State StartState::Update(float deltaTime)
{
	PlaySong();
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		mStartPlaying = false;
		PlaySong();
		X::PlaySoundOneShot(mSoundId2);
		return State::RunGame;
	}
	
	return State::Start;
}

void StartState::Render()
{
	X::Math::Vector2 backgroundPos = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
	X::DrawSprite(mBackgroundId, backgroundPos);
}

void StartState::Unload()
{
}

void StartState::PlaySong()
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
