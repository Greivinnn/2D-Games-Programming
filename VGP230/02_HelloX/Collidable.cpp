#include <XEngine.h>
#include "Collidable.h"


Collidable::Collidable(float radius)
	: mRadius(radius)
	, mCollisionFilter(-1)
{
	
}

Collidable::~Collidable()
{
}


void Collidable::SetCollisionFilter(int filter)
{
	mCollisionFilter = filter;
}

int Collidable::GetCollisionFilter() const
{
	return mCollisionFilter;
}
float Collidable::GetRadius() const
{
	return mRadius;
}
bool Collidable::DidCollide(const Collidable* collidable) const
{
	if (collidable == nullptr)
	{
		return false;
	}

	int collidableFilter = collidable->GetCollisionFilter();
	int collisionFilter = GetCollisionFilter();

	if (collidableFilter == 0 || collisionFilter == 0)
	{
		return false;
	}

	if (collidableFilter < 0 || collisionFilter < 0 || (collidableFilter & collisionFilter) > 0)
	{
		float distSq = X::Math::Vector2::SqrMagnitude(collidable->GetPosition() - GetPosition());
		float radiusSq = X::Math::Sqr(collidable->GetRadius() + GetRadius());
		return distSq <= radiusSq;
	}

	return false;
}