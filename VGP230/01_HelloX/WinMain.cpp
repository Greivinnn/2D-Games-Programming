#include <XEngine.h>
// This includes XEngine library, gives access to functions like LoadTexture()

X::TextureId imageId = 0;
X::Math::Vector2 imagePosition = { 0.0f, 0.0f };
float imageRotation = 0.0f;
// imageId: stores the ID of the texture (the loading image)
// imagePosition: hold the (x, y) coordinates of where to drae the image on screen
// imageRotation: the rotation angle (in degrees or radians depending on engine) of the sprite
// These are set as global variables so it can be used by all functions

void GameInit()
{
	imageId = X::LoadTexture("mario_walk_02.png");
	imagePosition.x = X::GetScreenWidth() * 0.5f;
	imagePosition.y = X::GetScreenHeight() * 0.5f;
	// LoadTexture(): loads your Mario image from the file and returns a texture ID
	// GetScreenWidth()/GetScreenHeight(): get the dimensions of the game window
	// it then sets the Mario starting position to the center of the screen (half width, half height)
}

void GameRender()
{
	X::DrawSprite(imageId, imagePosition, imageRotation);
	// DrawSprite(): draws the loaded image (imageId) on the screen at the given position and rotation
	// Every frame, this is what displays the Mario sprite
}

bool GameLoop(float deltaTime)
{
	// GameLoop(): this function runs every frame 
	// the engine calls it automatically many times per second (e.g., 60 times/sec)
	const float moveSpeed = 250.0f;
	const float rotationSpeed = 100.0f;
	// These are the speeds for movement and rotation
	if (X::IsKeyDown(X::Keys::UP))
	{
		imagePosition.y -= moveSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::DOWN))
	{
		imagePosition.y += moveSpeed * deltaTime;
	}
	// Moves the image up or down basesd on arrow key input 
	// deltaTime = the time passed since the last frame, so movement stays smooth and consistent no matter the framrate 
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		imagePosition.x -= moveSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::RIGHT))
	{
		imagePosition.x += moveSpeed * deltaTime;
	}
	// same here but left or right logic
	if (X::IsKeyDown(X::Keys::N))
	{
		imageRotation -= rotationSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::M))
	{
		imageRotation += rotationSpeed * deltaTime;
	}
	// this part is to rotate the mario left or right
	XLOG("Game Loop");
	GameRender();
	// Calls GameRender() every loop to update the sprite
	return X::IsKeyPressed(X::Keys::ESCAPE);
	// if ESC is pressed the window closes
}

void GameCleanup()
{
	XLOG("Game Cleanup");
	// Called when the game ends, here is where we would normally free memory or unload assets
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// main function 
	
	X::Start("xconfig.json");
	// X::Start(): Initializes the XEngine using the configuration file (xconfig.json)
	
	GameInit();
	// GameInit(): Loads textures and setups variables

	X::Run(GameLoop);
	// X::RUN(GameLoop): Starts the main loop, repeatedly calling GameLoop every frame

	GameCleanup();
	// GameCleanup(): Called when the loop ends (in this case when you press ESC)

	X::Stop();
	// X:Stop(): Shuts down the engine properly

	return 0;
}

// Summary
// GameInit(): Loads resources and sets starting values
// GameLoop(): Handles input, updates position/rotation, and renders
// GameRender(): Draws the sprite to the screen 
// GameCleanup(): Cleans up when the game ends
// WinMain(): Initializes and runs the whole game loop