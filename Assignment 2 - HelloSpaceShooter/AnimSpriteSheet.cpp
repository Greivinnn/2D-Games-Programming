#include "AnimSpriteSheet.h"

AnimSpriteSheet::AnimSpriteSheet()
	:Entity()
	, mSpriteSheetId(0)
	, mSpriteRect()
	, mPosition(0.0f, 0.0f)
	, mFrameRate(0.0f)
	, mCurrentFrameTime(0.0f)
	, mRows(0)
	, mColumns(0)
	, mMaxFrames(0)
	, mCurrentIndex(0)
	, mIsLooping(false)
	, mExplosionSound(0)
	, mHasPlayedSound(false)
{

}
AnimSpriteSheet::~AnimSpriteSheet()
{

}


//Entity overrides
void AnimSpriteSheet::Load() 
{
	mSpriteSheetId = X::LoadTexture("explosion_anim.png");
	mExplosionSound = X::LoadSound("explosion.wav");
	mSpriteRect.right = 100.0f;
	mSpriteRect.bottom = 100.0f;
	mMaxFrames = 81;
	mRows = 9;
	mColumns = 9;
	mFrameRate = 1.0f / 120.0f;
	mIsLooping = false;
	mCurrentIndex = -1;
}
void AnimSpriteSheet::Update(float deltaTime) 
{
	if (IsActive())
	{

		if (!mHasPlayedSound)
		{
			X::PlaySoundOneShot(mExplosionSound);
			mHasPlayedSound = true;
		}
		mCurrentFrameTime += deltaTime;
		while (mCurrentFrameTime > mFrameRate)
		{
			mCurrentFrameTime -= mFrameRate;
			++mCurrentIndex;
		}

		if(mCurrentIndex >= mMaxFrames)
		{
			if (mIsLooping)
			{
				mCurrentIndex -= mMaxFrames;
			}
			else
			{
				mCurrentIndex = -1;
			}
		}

		const float recWidth = 100.0f;
		const float recHeight = 100.0f;
		mSpriteRect.left = (mCurrentIndex % mColumns) * recWidth;
		mSpriteRect.top = (mCurrentIndex / mColumns) * recHeight;
		mSpriteRect.right = mSpriteRect.left + recWidth;
		mSpriteRect.bottom = mSpriteRect.top + recHeight;
		
	}
}
void AnimSpriteSheet::Render()
{
	if(IsActive())
	{
		X::DrawSprite(mSpriteSheetId, mSpriteRect, mPosition);
	}
}
void AnimSpriteSheet::Unload()
{

}

//AnimSpriteSheet functions
void AnimSpriteSheet::SetActive(const X::Math::Vector2& position, bool loop)
{
	mPosition = position;
	mIsLooping = loop;
	mCurrentIndex = 0;
	mCurrentFrameTime = 0.0f;
	mHasPlayedSound = false;
}
bool AnimSpriteSheet::IsActive() const
{
	return mIsLooping || mCurrentIndex >= 0;
}