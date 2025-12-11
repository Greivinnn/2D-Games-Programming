#pragma once

#include "Enum.h"
#include <map>	

class State;

class FSMController
{
public:
	FSMController();
	~FSMController();

	void AddState(MovementState moveState, State* state);
	void SetState(MovementState state);
	void Update(float deltaTime);
	void CleanUp();
private:
	MovementState mCurrentState;
	std::map<MovementState, State*> mStates;
};
