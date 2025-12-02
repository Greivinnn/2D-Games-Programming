#include <XEngine.h>
#include "Collidable.h"


Collidable::Collidable()
	: mCollisionFilter(-1)
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

void Collidable::SetRect(const X::Math::Rect& rect)
{
	mRect = rect;
}	

const X::Math::Rect& Collidable::GetRect() const
{
	return mRect;
}

bool Collidable::DidCollide(const Collidable* collidable) const
{
	if(collidable == nullptr)
	{
		return false;
	}

	int collidableFilter = collidable->GetCollisionFilter();
	int collisionFilter = GetCollisionFilter();
	if(collidableFilter == 0 || collisionFilter == 0)
	{
		return false;
	}

	if (collidableFilter < 0 || collisionFilter < 0 || (collidableFilter & GetType()) > 0)
	{
		return X::Math::Intersect(mRect, collidable->GetRect());
	}

	return false;
}