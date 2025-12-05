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
}
void WalkState::OnExitState()
{

}



JumpState::JumpState(Player* player)
	:
{

}
JumpState::~JumpState()
{

}

void JumpState::OnEnterState()
{

}
MovementState JumpState::Update(float deltaTime)
{

}
void JumpState::OnExitState()
{

}

FallState::FallState(Player* player)
	:
{

}
FallState::~FallState()
{

}

void FallState::OnEnterState()
{

}
MovementState FallState::Update(float deltaTime)
{

}
void FallState::OnExitState()
{

}
