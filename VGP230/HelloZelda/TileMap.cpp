#include "TileMap.h"

TileMap* TileMap::mInstance = nullptr;


TileMap::TileMap()
    : Entity(), mColumns(0), mRows(0)
{

}

TileMap::~TileMap()
{

}

TileMap* TileMap::Get()
{
    if (mInstance == nullptr)
    {
        mInstance = new TileMap();
    }

    return mInstance;
}

void TileMap::Load()
{
    ReloadMap();
}

void TileMap::Update(float deltaTime)
{
    if (X::IsKeyPressed(X::Keys::ENTER))
    {
        ReloadMap();
    }

    for (Tile* tile : mTiles)
    {
        tile->Update(deltaTime);
    }
}

void TileMap::Render()
{
    for (Tile* tile : mTiles)
    {
        tile->Render();
    }
}

void TileMap::Unload()
{
    for (Tile* tile : mTiles)
    {
        tile->Unload();
        delete tile;
        tile = nullptr;
    }

    mTiles.clear();
}

const Tile* TileMap::GetFirstWalkableTile()
{
    Tile* walkableTile = nullptr;

    for (Tile* tile : mTiles)
    {
        if (!tile->IsCollidable())
        {
            walkableTile = tile;
            break;
        }
    }

    return walkableTile;
}

void TileMap::ObtainAllWalkableTiles(std::vector<Tile*>& outWalkableTiles)
{
    for (Tile* tile : mTiles)
    {
        if (tile->IsCollidable() == false)
        {
            outWalkableTiles.push_back(tile);
        }
    }
}

bool TileMap::HasCollision(const X::Math::Rect& objRect, const X::Math::Vector2& maxDisplacement, X::Math::Vector2& outDisplacement) const
{
    // AABB
    // check x left/right
    // check y up/down

    bool hasCollision = false;
    const float offset = 0.5f;

    for (int d = 0; d < 2; ++d)
    {
        X::Math::Rect targetRect(objRect);
        X::Math::Vector2 testDirection = X::Math::Vector2::Zero();

        if (d == 0)
        {
            testDirection.x = maxDisplacement.x;
        }
        else
        {
            testDirection.y = maxDisplacement.y;
        }

        targetRect.min += testDirection;
        targetRect.max += testDirection;

        for (const Tile* tile : mTiles)
        {
            if (tile->IsCollidable() == true && tile->HasCollision(targetRect))
            {
                hasCollision = true;
                const X::Math::Rect& tileRect = tile->GetRect();

                if (d == 0)
                {
                    if (maxDisplacement.x > 0.0f && targetRect.right > tileRect.left)
                    {
                        outDisplacement.x = X::Math::Min(maxDisplacement.x - (targetRect.right - tileRect.left) - offset, outDisplacement.x);
                        outDisplacement.x = X::Math::Max(outDisplacement.x, 0.0f);
                    }
                    else if (maxDisplacement.x < 0.0f && targetRect.left < targetRect.right)
                    {
                        outDisplacement.x = X::Math::Max(maxDisplacement.x + (tileRect.right - targetRect.left) + offset, outDisplacement.x);
                        outDisplacement.x = X::Math::Min(outDisplacement.x, 0.0f);
                    }
                }
                else
                {
                    if (maxDisplacement.y < 0.0f && targetRect.top < tileRect.bottom)
                    {
                        outDisplacement.y = X::Math::Max(maxDisplacement.y + (tileRect.bottom - targetRect.top) + offset, outDisplacement.y);
                        outDisplacement.y = X::Math::Min(outDisplacement.y, 0.0f);
                    }
                    else
                    {
                        outDisplacement.y = X::Math::Min(maxDisplacement.y - (targetRect.bottom - tileRect.top) - offset, outDisplacement.y);
                        outDisplacement.y = X::Math::Max(outDisplacement.y, 0.0f);
                    }
                }
            }
        }
    }

    return hasCollision;
}

void TileMap::ReloadMap()
{
    const char fileName[255] = "./level.lvl";
    std::fstream inputStream;
    inputStream.open(fileName);

    inputStream >> mColumns;
    inputStream >> mRows;

    X::TextureId dummyTile = X::LoadTexture("white.jpg");
    const float tileWidth = X::GetSpriteWidth(dummyTile);
    const float tileHeight = X::GetSpriteHeight(dummyTile);

    Unload();
    X::Math::Vector2 offset = { tileWidth * 0.5f, tileHeight * 0.5f };

    int dataType = 0;
    int tileIndex = 0;
    int x = 0;
    int y = 0;

    while (inputStream >> dataType)
    {
        X::Math::Vector2 position = X::Math::Vector2::Zero();
        TileType tileType = (TileType)dataType;
        x = tileIndex % mColumns;
        y = tileIndex / mColumns;
        position.x = tileWidth * x + offset.x;
        position.y = tileHeight * y + offset.y;

        Tile* newTile = new Tile(tileType, position);
        newTile->Load();
        mTiles.push_back(newTile);
        ++tileIndex;
    }
}