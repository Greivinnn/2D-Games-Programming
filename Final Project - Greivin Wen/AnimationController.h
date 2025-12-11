#pragma once
#include "Animation.h"
#include <map>
#include <string>

class AnimationController
{
public:
    AnimationController();
    ~AnimationController();

    void AddAnimation(const std::string& name, Animation* animation);
    void SetCurrentAnimation(const std::string& name);

    void Update(float deltaTime);
    void Render(const X::Math::Vector2& position);

    Animation* GetAnimation(const std::string& name);
    const std::string& GetCurrentAnimationName() const;

private:
    std::map<std::string, Animation*> mAnimations;
    std::string mCurrentAnimationName;
    Animation* mCurrentAnimation;
};