#include "EnemyTest.h"

#include "Texture.h"
#include "Timer.h"
#include "EnemyManager.h"
#include "BoxCollider.h"
#include "Projectile.h"

EnemyTest::EnemyTest()
{
	mTexture = new Texture("SpaceShipSpriteSheet.png", 0, 0, 40, 38);
	mTexture->Parent(this);
	mtimer = Timer::Instance();
	mEMgr = EnemyManager::Instance();
	mEMgr->AddToEnemyList(this);
	mActive = true;
	mcurrentState = Moving;
	Rotation(90);
	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
}



EnemyTest::~EnemyTest()
{
	mtimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void EnemyTest::Update()
{
	if (mActive)
	{		
		switch (mcurrentState)
		{
		case Waiting:
			WaitingState();
			Fire();
			break;

		case Moving:
			MovingState();
			Fire();
			break;
		
		case Dying:
			DyingState();
			break;
		}
	}
}

void EnemyTest::WaitingState()
{
	
	mwaitTimer = mwaitTimer + mtimer->DeltaTime();
	if (mwaitTimer >=  mwaitTime)
	{
		mcurrentState = Moving;
		mwaitTimer = 0;
	}
}

void EnemyTest::MovingState()
{

	if (mgotPath == false)
	{
		currentTargetVec = mEMgr->newPath(this);
		std::cout << "Getting pos" << std::endl;
		mgotPath = true;
	}

	
	Translate(MoveTowards(currentTargetVec) * mspeed * mtimer->DeltaTime());
	if (GetPos().x == currentTargetVec.x && GetPos().y == currentTargetVec.y)
	{
		std::cout << "Arrived" << std::endl;
		mgotPath = false;
		mcurrentState = Waiting;
	}
}

void EnemyTest::DyingState()
{
	float t =0;
	t = t + mtimer->DeltaTime();
	if (t >= 3/1) // timer >= framecount / animSpeed
	{
		mActive = false;
	}

}

void EnemyTest::Fire()
{
	
	mfireTimer = mfireTimer + mtimer->DeltaTime();
	if (mfireTimer >= mfireRate)
	{
		new Projectile(GetPos(), GetRotation(), 1000);
		mfireTimer = 0;
	}
	
}

void EnemyTest::Render()
{
	mTexture->Render();
}
