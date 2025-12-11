#include "States.h"
#include "Player.h"	
#include "TileMap.h"

const float cWalkSpeed = 200.0f;
const float cJumpSpeed = 300.0f;
const float cFrictionAccel = 600.0f;
const float cFallAccel = 300.0f;
const float cMaxWalkSpeed = 300.0f;
const float cMaxFallSpeed= 300.0f;

IdleState::IdleState(Player* player)
	: State(player)
{

}
IdleState::~IdleState()
{

}

void IdleState::OnEnterState()
{

}
MovementState IdleState::Update(float deltaTime)
{
	if(X::IsKeyDown(X::Keys::A) || X::IsKeyDown(X::Keys::D))
	{
		return MS_WALK;
	}
	if(X::IsAPressed(X::Keys::W))
	{
		return MS_JUMP;
	}
	return MS_IDLE;
}
void IdleState::OnExitState()
{

}


WalkState::WalkState(Player* player)
	:State(player)
	, mVelocity(0.0f, 0.0f)
{

}
WalkState::~WalkState()
{

}

void WalkState::OnEnterState()
{
	mVelocity = mPlayer->GetVelocity();
}
MovementState WalkState::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::W))
	{
		return MS_JUMP;
	}
	if (X::IsKeyDown(X::Keys::A))
	{
		if(mVelocity.x > 0.0f)
		{
			mVelocity.x -= 2.0 * (cWalkSpeed + cFrictionAccel) * deltaTime;
		}	
		else
		{
			mVelocity -= cWalkSpeed * deltaTime;
		}
		mVelocity.x = X::Math::Max(mVelocity.x, -cMaxWalkSpeed);
	}
	else if (X::IsKeyDown(X::Keys::D))
	{
		if(mVelocity.x < 0.0f)
		{
			mVelocity.x += 2.0 * (cWalkSpeed + cFrictionAccel) * deltaTime;
		}	
		else
		{
			mVelocity += cWalkSpeed * deltaTime;
		}
		mVelocity.x = X::Math::Min(mVelocity.x, cMaxWalkSpeed);
	}
	else
	{
		if (mVelocity.x < 0.0f)
		{
			mVelocity.x += cFrictionAccel * deltaTime;
		}
		else if (mVelocity.x > 0.0f)
		{
			mVelocity.x -= cFrictionAccel * deltaTime;
		}
		if (abs(mVelocity.x) < 0.1f)
		{
			mVelocity.x = 0.0f;
			mPlayer->SetVelocity(mVelocity);
			return MS_IDLE;
		}
	}
	X::Math::Vector2 displacement;
	displacement.x = mVelocity.x * deltaTime;
	displacement.y = cWalkSpeed * deltaTime;
	X::Math::Vector2 position = mPlayer->GetPosition();
	X::Math::Vector2 maxDisplacement = displacement;
	if (TileMap::Get()->HasCollision(mPlayer->GetRect(), maxDisplacement, displacement))
	{
		//XLOG("hit wall");
	}
	position += displacement;
	
	mPlayer->SetVelocity(mVelocity);
	mPlayer->SetPosition(position);

	if(displacement.y > 0.0f)
	{
		return MS_FALL;
	}
	return MS_WALK;
}
void WalkState::OnExitState()
{

}



JumpState::JumpState(Player* player)
	: State(player)
	, mVelocity(0.0f, 0.0f)
{

}
JumpState::~JumpState()
{

}

void JumpState::OnEnterState()
{
	mVelocity = mPlayer->GetVelocity();
	mVelocity.y = -cJumpSpeed;
}
MovementState JumpState::Update(float deltaTime)
{
	if (X::IsKeyDown(X::Keys::A))
	{
		mVelocity.x -= cWalkSpeed * deltaTime;
		mVelocity.x = X::Math::Max(mVelocity.x, -cMaxWalkSpeed);
	}
	else if (X::IsKeyDown(X::Keys::D))
	{
		mVelocity.x += cWalkSpeed * deltaTime;
		mVelocity.x = X::Math::Min(mVelocity.x, cMaxWalkSpeed);
	}
	else
	{
		if (mVelocity.x < 0.0f)
		{
			mVelocity.x += cFrictionAccel * 0.5 * deltaTime;
		}
		else if (mVelocity.x > 0.0f)
		{
			mVelocity.x -= cFrictionAccel * 0.5 * deltaTime;
		}
		if(abs(mVelocity.x) < 0.1f)
		{
			mVelocity.x = 0.0f;
		}
	}
	mVelocity.y += cFallAccel * deltaTime;
	X::Math::Vector2 displacement = mVelocity * deltaTime;
	X::Math::Vector2 maxDisplacement = displacement;
	X::Math::Vector2 position = mPlayer->GetPosition();
	if(TileMap::Get()->HasCollision(mPlayer->GetRect(), maxDisplacement, displacement))
	{
		
	}
	position += displacement;
	mPlayer->SetVelocity(mVelocity);
	mPlayer->SetPosition(position);
	if (mVelocity.y > 0.0f)
	{
		return MS_FALL;
	}
	return MS_JUMP;
}
void JumpState::OnExitState()
{

}

FallState::FallState(Player* player)
	: State(player)
	, mVelocity(0.0f, 0.0f)
{

}
FallState::~FallState()
{

}

void FallState::OnEnterState()
{
	mVelocity = mPlayer->GetVelocity();
}
MovementState FallState::Update(float deltaTime)
{
	if (X::IsKeyDown(X::Keys::A))
	{
		mVelocity.x -= cWalkSpeed * deltaTime;
		mVelocity.x = X::Math::Max(mVelocity.x, -cMaxWalkSpeed);
	}
	else if (X::IsKeyDown(X::Keys::D))
	{
		mVelocity.x += cWalkSpeed * deltaTime;
		mVelocity.x = X::Math::Min(mVelocity.x, cMaxWalkSpeed);
	}
	else
	{
		if (mVelocity.x < 0.0f)
		{
			mVelocity.x += cFrictionAccel * 0.5 * deltaTime;
		}
		else if (mVelocity.x > 0.0f)
		{
			mVelocity.x -= cFrictionAccel * 0.5 * deltaTime;
		}
		if (abs(mVelocity.x) < 0.1f)
		{
			mVelocity.x = 0.0f;
		}
	}
	mVelocity.y += cFallAccel * deltaTime;
	X::Math::Vector2 displacement = mVelocity * deltaTime;
	X::Math::Vector2 maxDisplacement = displacement;
	X::Math::Vector2 position = mPlayer->GetPosition();
	if (TileMap::Get()->HasCollision(mPlayer->GetRect(), maxDisplacement, displacement))
	{

	}
	position += displacement;
	mPlayer->SetVelocity(mVelocity);
	mPlayer->SetPosition(position);
	if(displacement.y < maxDisplacement.y)
	{
		if(abs(displacement.x) > 0.0f)
		{
			return MS_WALK;
		}
		return MS_IDLE;
	}
	return MS_FALL;
}
void FallState::OnExitState()
{

}
