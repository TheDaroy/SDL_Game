#pragma once
#include "PhysEntity.h"

namespace QuickSDL
{
	class Texture;
	class Timer;
	
}
class EnemyManager;
using namespace QuickSDL;
class EnemyTest : public PhysEntity
{
public:

	EnemyTest();
	~EnemyTest();
	bool mActive = false;
	unsigned int id;
	void Update();

	void WaitingState();
	void MovingState();
	void DyingState();
	void Fire();
	void Render();
	Texture* mTexture;
	Vector2 currentTargetVec;
private:

	Timer* mtimer;
	EnemyManager* mEMgr;
	enum States { Waiting, Moving, Dying };
	States mcurrentState;
	bool mgotPath = false;
	float mspeed = 70;

	float mfireRate = 1;
	float mfireTimer = 0;
	const int mwaitTime = 3;
	float mwaitTimer = 0;
	
};

