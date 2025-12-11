#include "Animation.h"

Animation::Animation()
    : mFrameDuration(0.15f)
    , mAnimationTimer(0.0f)
    , mCurrentFrame(0)
    , mLoop(true)
    , mFinished(false)
{
}

Animation::~Animation()
{
}

void Animation::AddFrame(const char* filename)
{
    X::TextureId textureId = X::LoadTexture(filename);
    mFrames.push_back(textureId);
}

void Animation::SetFrameDuration(float duration)
{
    mFrameDuration = duration;
}

void Animation::SetLooping(bool loop)
{
    mLoop = loop;
}

void Animation::Update(float deltaTime)
{
    if (mFrames.empty() || mFinished)
    {
        return;
    }

    mAnimationTimer += deltaTime;

    if (mAnimationTimer >= mFrameDuration)
    {
        mAnimationTimer = 0.0f;
        mCurrentFrame++;

        if (mCurrentFrame >= mFrames.size())
        {
            if (mLoop)
            {
                mCurrentFrame = 0;
            }
            else
            {
                mCurrentFrame = mFrames.size() - 1;
                mFinished = true;
            }
        }
    }
}

void Animation::Reset()
{
    mCurrentFrame = 0;
    mAnimationTimer = 0.0f;
    mFinished = false;
}

X::TextureId Animation::GetCurrentFrame() const
{
    if (mFrames.empty())
    {
        return 0;
    }
    return mFrames[mCurrentFrame];
}

bool Animation::IsFinished() const
{
    return mFinished;
}

int Animation::GetFrameCount() const
{
    return mFrames.size();
}