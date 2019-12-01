#include "Projectile.h"
#include "Texture.h"
#include "Timer.h"
#include "EnemyManager.h"
#include "BoxCollider.h"
#include "MathHelper.h"
#include <iostream>

Projectile::Projectile(Vector2 pos ,float rot = 0, float speed = 50)
{
	mTexture = new Texture("SpaceShipSpriteSheet.png", 6, 135, 5, 11);
	mTexture->Parent(this);
	mTexture->Scale(GetScale()*2);
	//AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
	Pos(pos);
	mActive = true;
	mSpeed = speed;
	mtimer = Timer::Instance();
	mEMgr = EnemyManager::Instance();
	Rotation(rot);
	std::cout << "New Projectile" << std::endl;
	std::cout << GetPos().x << " : " << GetPos().y<< std::endl;
	mEMgr->AddToProjectileList(this);
}

Projectile::~Projectile()
{
}

void Projectile::Render()
{
	mTexture->Render();
}


void Projectile::Update()
{
	MoveForward(15);
}
