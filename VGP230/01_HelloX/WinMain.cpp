#include <XEngine.h>


X::TextureId imageId = 0;
X::Math::Vector2 imagePosition = { 0.0f, 0.0f };
float imageRotation = 0.0f;

void GameInit()
{
	imageId = X::LoadTexture("mario_walk_02.png");
	imagePosition.x = X::GetScreenWidth() * 0.5f;
	imagePosition.y = X::GetScreenHeight() * 0.5f;
}

void GameRender()
{
	X::DrawSprite(imageId, imagePosition, imageRotation);
}

bool GameLoop(float deltaTime)
{
	// Do inputs and effects
	const float moveSpeed = 250.0f;
	const float rotationSpeed = 100.0f;
	if (X::IsKeyDown(X::Keys::UP))
	{
		imagePosition.y -= moveSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::DOWN))
	{
		imagePosition.y += moveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		imagePosition.x -= moveSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::RIGHT))
	{
		imagePosition.x += moveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::N))
	{
		imageRotation -= rotationSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::M))
	{
		imageRotation += rotationSpeed * deltaTime;
	}
	// Do physics and physics result
	// Render Final Positions
	XLOG("Game Loop");
	GameRender();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	XLOG("Game Cleanup");
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;
}