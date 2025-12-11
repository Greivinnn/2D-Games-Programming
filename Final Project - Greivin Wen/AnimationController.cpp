#include "AnimationController.h"

AnimationController::AnimationController()
    : mCurrentAnimation(nullptr)
{
}

AnimationController::~AnimationController()
{
    for (auto& pair : mAnimations)
    {
        delete pair.second;
        pair.second = nullptr;
    }
    mAnimations.clear();
}

void AnimationController::AddAnimation(const std::string& name, Animation* animation)
{
    mAnimations[name] = animation;

    if (mCurrentAnimation == nullptr)
    {
        mCurrentAnimation = animation;
        mCurrentAnimationName = name;
    }
}

void AnimationController::SetCurrentAnimation(const std::string& name)
{
    if (mCurrentAnimationName == name)
    {
        return;
    }

    auto it = mAnimations.find(name);
    if (it != mAnimations.end())
    {
        mCurrentAnimation = it->second;
        mCurrentAnimation->Reset();
        mCurrentAnimationName = name;
    }
}

void AnimationController::Update(float deltaTime)
{
    if (mCurrentAnimation != nullptr)
    {
        mCurrentAnimation->Update(deltaTime);
    }
}

void AnimationController::Render(const X::Math::Vector2& position)
{
    if (mCurrentAnimation != nullptr)
    {
        X::DrawSprite(mCurrentAnimation->GetCurrentFrame(), position);
    }
}

Animation* AnimationController::GetAnimation(const std::string& name)
{
    auto it = mAnimations.find(name);
    if (it != mAnimations.end())
    {
        return it->second;
    }
    return nullptr;
}

const std::string& AnimationController::GetCurrentAnimationName() const
{
    return mCurrentAnimationName;
}