#include "EndState.h"
#include <XEngine.h>

EndState::EndState()
	:GameState(State::End)
{
}

EndState::~EndState()
{
}

void EndState::Load()
{
}

State EndState::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		return State::Start;
	}

	return State::End;
}

void EndState::Render()
{
	const float textSize = 100.0f;
	const char* text = "\n\n<END GAME STATE>";
	float textWidth = X::GetTextWidth(text, textSize);
	float screenX = (X::GetScreenWidth() - textWidth) * 0.5f;
	float screenY = (X::GetScreenHeight() - textWidth) * 0.5f;
	X::DrawScreenText(text, screenX, screenY, textSize, X::Colors::Green);
}

void EndState::Unload()
{
}
