#include "EnemyTest.h"

EnemyTest::EnemyTest()
{
	mTexture = new Texture("SpaceShipSpriteSheet.png", 0, 0, 40, 38);
	mtimer = Timer::Instance();
	mActive = true;
}



EnemyTest::~EnemyTest()
{
}

void EnemyTest::Update()
{
	if (mActive)
	{
		States test;
		switch (test)
		{
		case EnemyTest::Waiting:

			break;

		case EnemyTest::Moving:
			break;
		

		}


	}
}
