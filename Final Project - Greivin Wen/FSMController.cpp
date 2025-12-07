#include "FSMController.h"
#include "States.h"

FSMController::FSMController()
	: mCurrentState(MS_NONE)
{
}
FSMController::~FSMController()
{

}

void FSMController::AddState(MovementState moveState, State* state)
{
	XASSERT(mStates[moveState] == nullptr, "FSMCOnterller: state already exist");
	mStates[moveState] = state;
}
void FSMController::SetState(MovementState state)
{
	if (mCurrentState != state)
	{
		if (mStates[mCurrentState] != nullptr)
		{
			mStates[mCurrentState]->OnExitState();
		}
		mCurrentState = state;
		if (mStates[mCurrentState] != nullptr)
		{
			mStates[mCurrentState]->OnEnterState();
		}
	}
}
void FSMController::Update(float deltaTime)
{
	if (mStates[mCurrentState] != nullptr)
	{
		MovementState nextState = mStates[mCurrentState]->Update(deltaTime);
		SetState(nextState);
	}
}
void FSMController::CleanUp()
{
	if (mStates[mCurrentState] != nullptr)
	{
		mStates[mCurrentState]->OnExitState();
	}
	for (auto keyPair : mStates)
	{
		delete keyPair.second;
		keyPair.second = nullptr;
	}
	mStates.clear();
}