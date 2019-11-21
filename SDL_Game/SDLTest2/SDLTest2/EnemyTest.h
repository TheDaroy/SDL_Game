#pragma once
#include "GameEntity.h"
#include "Texture.h"
#include "Timer.h"
using namespace QuickSDL;

class EnemyTest : public GameEntity
{
public:
	
	EnemyTest();
	~EnemyTest();
	bool mActive = false;
	void Update();
private:
	Texture* mTexture;
	Timer* mtimer;
	enum States { Waiting, Moving };
};

