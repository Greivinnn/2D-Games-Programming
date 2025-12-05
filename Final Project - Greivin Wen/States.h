#pragma once

#include <XEngine.h>
#include "Enum.h"

class Player;

class State
{
public:
	State(Player* player) : mPlayer(player) {}
	virtual ~State() {}

	virtual void OnEnterState() = 0;
	virtual MovementState Update(float deltaTime) = 0;
	virtual void OnExitState() = 0;

protected: 
	Player* mPlayer;
};

class IdleState : public State
{
public:
	IdleState(Player* player);
	~IdleState() override;

	void OnEnterState() override;
	MovementState Update(float deltaTime) override;
	void OnExitState() override;

};

class WalkState : public State
{
public:
	WalkState(Player* player);
	~WalkState() override;

	void OnEnterState() override;
	MovementState Update(float deltaTime) override;
	void OnExitState() override;
private:
	X::Math::Vector2 mVelocity;
};

class JumpState : public State
{
public:
	JumpState(Player* player);
	~JumpState() override;

	void OnEnterState() override;
	MovementState Update(float deltaTime) override;
	void OnExitState() override;
private:
	X::Math::Vector2 mVelocity;
};

class FallState : public State
{
public:
	FallState(Player* player);
	~FallState() override;

	void OnEnterState() override;
	MovementState Update(float deltaTime) override;
	void OnExitState() override;
private:
	X::Math::Vector2 mVelocity;
};