#pragma once
#include "Tile.h"

class TileMap : public Entity
{
public:
    ~TileMap() override;

    static TileMap* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    const Tile* GetFirstWalkableTile();
    void ObtainAllWalkableTiles(std::vector<Tile*>& outWalkableTiles);
    bool HasCollision(const X::Math::Rect& objRect, const X::Math::Vector2& maxDisplacement, X::Math::Vector2& outDisplacement) const;

private:
    TileMap();
    static TileMap* mInstance;

    void ReloadMap();

    std::vector<Tile*> mTiles;
    int mColumns;
    int mRows;
};