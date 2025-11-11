#pragma once
#include "GameState.h"
#include "Entity.h"

class StartState : public GameState
{
public:
	StartState();
	~StartState() override;

	void Load() override;
	State Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void PlaySong();
private:
	X::TextureId mBackgroundId;
	X::SoundId mSoundId;
	X::SoundId mSoundId2;
	bool mStartPlaying;
};