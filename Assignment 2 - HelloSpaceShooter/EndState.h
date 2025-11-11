#pragma once
#include "GameState.h"
#include "Entity.h"

class EndState : public GameState
{
public:
	EndState();
	~EndState() override;

	void Load() override;
	State Update(float deltaTime) override;
	void Render() override;
	void Unload() override;
	void PlaySong();
private:
	X::TextureId mBackgroundId;
	X::SoundId mSoundId;
	bool mStartPlaying;
};