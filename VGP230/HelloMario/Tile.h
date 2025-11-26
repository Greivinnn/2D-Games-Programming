#pragma once
#include "Entity.h"
#include "Enum.h"

class Tile : public Entity
{
public:
	Tile(TileType tileType, const X::Math::Vector2& position);
	~Tile() override;

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	const X::Math::Vector2& GetPosition() const;
	bool IsCollidable() const;
	bool HasCollision(const X::Math::Rect& objRect) const;
	const X::Math::Rect& GetRect() const;

private:
	TileType mTileType;
	X::Math::Vector2 mPosition;
	X::Math::Rect mRect;
	X::TextureId mImageId;
};
