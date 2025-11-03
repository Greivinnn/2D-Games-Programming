#pragma once
#include "Entity.h"

class AnimSpriteSheet : public Entity
{
public: 
	AnimSpriteSheet();
	~AnimSpriteSheet();


	//Entity overrides
	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	//AnimSpriteSheet functions
	void SetActive(const X::Math::Vector2& position, bool loop = false);
	bool IsActive() const;

private:
	X::TextureId mSpriteSheetId;
	X::Math::Rect mSpriteRect;
	X::Math::Vector2 mPosition;
	float mFrameRate;
	float mCurrentFrameTime;
	int mRows;
	int mColumns;
	int mMaxFrames;
	int mCurrentIndex;
	bool mIsLooping;
};