//#include "DiverEnemy.h"
//#include "Enemy.h"
//#include "Pool.h"
//#include "Bullet.h"
//#include "Ship.h"
//#include "AnimSpriteSheet.h"
//
//DiverEnemy::DiverEnemy()
//	: Entity()
//	, Collidable(30.0f)
//	, mBulletPool(nullptr)
//	, mShip(nullptr)
//	, mExplosion(nullptr)
//	, mImageId(0)
//	, mPosition(0.0f, 0.0f)
//	, mRotation(0.0f)
//	, mHealth(100)
//	, mCenterPoint(0.0f, 0.0f)
//	, mTargetPosition(0.0f, 0.0f)
//	, mTargetPositionUpdate(0.0f)
//	, mFireRate(0.0f)
//{
//}
//
//DiverEnemy::~DiverEnemy()
//{
//}
//
//void Enemy::Load()
//{
//	mImageId = X::LoadTexture("interceptor_01.png");
//	XASSERT(mImageId > 0, "Enemy: image did not load");
//
//	mPosition = X::Math::Vector2::Zero();
//	mRotation = 0.0f;
//
//	SetCollisionFilter(ET_BULLET_PLAYER | ET_SHIP);
//
//	mExplosion = new AnimSpriteSheet();
//	mExplosion->Load();
//
//	mTargetPositionUpdate = 0.0f;
//	mFireRate = 5.0f;
//
//}