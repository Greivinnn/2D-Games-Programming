#include "CollisionManager.h"
#include "Collidable.h"

CollisionManager* CollisionManager::mInstance = nullptr;

CollisionManager::CollisionManager()
    : Entity(), mShowCollidables(false)
{

}

CollisionManager::~CollisionManager()
{

}

CollisionManager* CollisionManager::Get()
{
    if (mInstance == nullptr)
    {
        mInstance = new CollisionManager();
    }

    return mInstance;
}

void CollisionManager::Load()
{

}

void CollisionManager::Update(float deltaTime)
{
    int numCollidables = mCollidables.size();

    for (int i = 0; i < numCollidables - 1; ++i)
    {
        for (int n = i + 1; n < numCollidables; ++n)
        {
            if (mCollidables[i]->DidCollide(mCollidables[n]))
            {
                mCollidables[i]->OnCollision(mCollidables[n]);
                mCollidables[n]->OnCollision(mCollidables[i]);
            }
        }
    }

    if (X::IsKeyPressed(X::Keys::I))
    {
        mShowCollidables = !mShowCollidables;
    }
}

void CollisionManager::Render()
{
    if (mShowCollidables == true)
    {
        for (Collidable* collidable : mCollidables)
        {
            X::DrawScreenRect(collidable->GetRect(), X::Colors::Red);
        }
    }
}

void CollisionManager::Unload()
{
    mCollidables.clear();
}

void CollisionManager::AddCollidable(Collidable* collidable)
{
    if (std::find(mCollidables.begin(), mCollidables.end(), collidable) == mCollidables.end())
    {
        mCollidables.push_back(collidable);
    }
}

void CollisionManager::RemoveCollidable(Collidable* collidable)
{
    auto iterator = std::find(mCollidables.begin(), mCollidables.end(), collidable);

    if (iterator != mCollidables.end())
    {
        mCollidables.erase(iterator);
    }
}