#pragma once
#include <XEngine.h>
#include <vector>

class Animation
{
public:
    Animation();
    ~Animation();

    void AddFrame(const char* filename);
    void SetFrameDuration(float duration);
    void SetLooping(bool loop);

    void Update(float deltaTime);
    void Reset();

    X::TextureId GetCurrentFrame() const;
    bool IsFinished() const;
    int GetFrameCount() const;

private:
    std::vector<X::TextureId> mFrames;
    float mFrameDuration;
    float mAnimationTimer;
    int mCurrentFrame;
    bool mLoop;
    bool mFinished;
};