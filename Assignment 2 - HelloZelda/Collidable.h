#pragma once
#include <math.h>
#include "Enum.h"

namespace X
{
	namespace Math	// forward declaration to let the compiler know "hey i exist"
	{
		class Vector2;
		class Rect;
	}
}

class Collidable
{
public:
	Collidable();
	virtual ~Collidable();

	virtual int GetType() const = 0;
	virtual const X::Math::Vector2& GetPosition() const = 0;
	virtual void OnCollision(Collidable* collidable) = 0;

	virtual void SetCollisionFilter(int filter);

	virtual int GetCollisionFilter() const;
	virtual void SetRect(const X::Math::Rect& rect);
	virtual const X::Math::Rect& GetRect() const;
	virtual bool DidCollide(const Collidable* collidable) const;

private:
	X::Math::Rect mRect;
	int mCollisionFilter;
};
