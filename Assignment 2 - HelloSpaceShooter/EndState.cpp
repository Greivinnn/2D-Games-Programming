#include "EndState.h"
#include <XEngine.h>

EndState::EndState()
	:GameState(State::End)
	, mBackgroundId(0)
	, mSoundId(0)
	, mStartPlaying(false)
{
}

EndState::~EndState()
{
}

void EndState::Load()
{
	mBackgroundId = X::LoadTexture("EndGameScreen.png");
	mSoundId = X::LoadSound("OutroSong.wav");
	mStartPlaying = true;
}

State EndState::Update(float deltaTime)
{
	PlaySong();
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		mStartPlaying = false;
		PlaySong();
		return State::Start;
	}

	return State::End;
}

void EndState::Render()
{
	X::Math::Vector2 backgroundPos = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
	X::DrawSprite(mBackgroundId, backgroundPos);
}

void EndState::Unload()
{
}

void EndState::PlaySong()
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

