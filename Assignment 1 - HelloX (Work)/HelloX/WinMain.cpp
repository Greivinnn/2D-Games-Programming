#include <XEngine.h>

// first logo sprite
X::TextureId imageId = 0;
X::Math::Vector2 imagePosition = { 0.0f, 0.0f };
float velocityX = 800.0f;
float velocityY = 800.0f;
float logoWidth = 0.0f;
float logoHeight = 0.0f;
// second logo sprite
X::TextureId imageId2 = 0;
X::Math::Vector2 imagePosition2 = { 0.0f, 0.0f };
float velocityX2 = 400.0f;
float velocityY2 = 400.0f;
float logoWidth2 = 0.0f;
float logoHeight2 = 0.0f;
void GameInit()
{
    // first sprite
	imageId = X::LoadTexture("cyberpunkBanner.png");
	imagePosition.x = X::GetScreenWidth() * 0.5f;
	imagePosition.y = X::GetScreenHeight() * 0.5f;
	// Loads the script and the start position of the image to appear in
	logoWidth = X::GetSpriteWidth(imageId);
	logoHeight = X::GetSpriteHeight(imageId); 
	// gets the dimension of our logo so we can use the variables for later

    // second sprite
    imageId2 = X::LoadTexture("geometryDash.png");
    imagePosition2.x = 0;
    imagePosition2.y = 0;
    logoWidth2 = X::GetSpriteWidth(imageId2);
    logoHeight2 = X::GetSpriteHeight(imageId2);
}

void GameRender()
{
	X::DrawSprite(imageId, imagePosition);
    X::DrawSprite(imageId2, imagePosition2);
    // Renders the image frame by fram updating it
}

bool GameLoop(float deltaTime)
{
	// Move logo
    imagePosition.x += velocityX * deltaTime;
    imagePosition.y += velocityY * deltaTime;

    imagePosition2.x += velocityX2 * deltaTime;
    imagePosition2.y += velocityY2 * deltaTime;

    // Half-size values (because my logo is centered)
    float halfWidth = logoWidth * 0.5f;
    float halfHeight = logoHeight * 0.5f;
    float halfWidth2 = logoWidth2 * 0.5f;
    float halfHeight2 = logoHeight2 * 0.5f;

    // Bounce on horizontal borders
    if (imagePosition.x - halfWidth <= 0.0f)
    {
        imagePosition.x = halfWidth; // keep inside
        velocityX = -velocityX;
    }
    else if (imagePosition.x + halfWidth >= X::GetScreenWidth())
    {
        imagePosition.x = X::GetScreenWidth() - halfWidth;
        velocityX = -velocityX;
    }

    // Bounce on vertical borders
    if (imagePosition.y - halfHeight <= 0.0f)
    {
        imagePosition.y = halfHeight;
        velocityY = -velocityY;
    }
    else if (imagePosition.y + halfHeight >= X::GetScreenHeight())
    {
        imagePosition.y = X::GetScreenHeight() - halfHeight;
        velocityY = -velocityY;
    }

    if (imagePosition2.x - halfWidth2 <= 0.0f)
    {
        imagePosition2.x = halfWidth2; // keep inside
        velocityX2 = -velocityX2;
    }
    else if (imagePosition2.x + halfWidth2 >= X::GetScreenWidth())
    {
        imagePosition2.x = X::GetScreenWidth() - halfWidth2;
        velocityX2 = -velocityX2;
    }
    if (imagePosition2.y - halfHeight2 <= 0.0f)
    {
        imagePosition2.y = halfHeight2;
        velocityY2 = -velocityY2;
    }
    else if (imagePosition2.y + halfHeight2 >= X::GetScreenHeight())
    {
        imagePosition2.y = X::GetScreenHeight() - halfHeight2;
        velocityY2 = -velocityY2;
    }
    // Draw the frame
    GameRender();

    // Exit key
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

