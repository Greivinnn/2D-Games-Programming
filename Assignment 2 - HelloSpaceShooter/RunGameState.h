#pragma once
#include "GameState.h"
#include "Entity.h"

class Game;

class RunGameState : public GameState
{
public:
	RunGameState();
	~RunGameState() override;

	void Load() override;
	State Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void PlaySong();
private:
	Game* mGame;
	X::SoundId mSoundId;
	bool mStartPlaying;
};
