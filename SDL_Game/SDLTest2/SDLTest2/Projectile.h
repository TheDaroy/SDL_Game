#pragma once
#include "PhysEntity.h"

namespace QuickSDL
{
	class Texture;
	class Timer;

}
class EnemyManager;
class Projectile : public PhysEntity
{
public:
	Projectile(Vector2 pos,float rot, float speed);
	~Projectile();
	void Render();
	void Update();

	bool mActive = false;
	float mSpeed;
	Texture* mTexture;
private:
	
	Timer* mtimer;
	EnemyManager* mEMgr;
};