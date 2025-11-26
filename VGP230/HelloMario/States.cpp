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
	, mVelocity(0.0f, 0.0f);
WalkState::~WalkState() override;

	void WalkState::OnEnterState() override;
	MovementState WalkState::Update(float deltaTime) override;
	void WalkState::OnExitState() override;



	JumpState::JumpState(Player* player);
	JumpState::~JumpState() override;

	void JumpState::OnEnterState() override;
	MovementState JumpState::Update(float deltaTime) override;
	void JumpState::OnExitState() override;

	FallState::FallState(Player* player);
	FallState::~FallState() override;

	void FallState::OnEnterState() override;
	MovementState FallState::Update(float deltaTime) override;
	void FallState::OnExitState() override;
