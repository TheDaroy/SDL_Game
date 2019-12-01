#ifndef _PLAYER_H
#define _PLAYER_H
#include"AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Bullet.h"

using namespace QuickSDL;

class Player : public GameEntity
{
private:
	Timer* mTimer;
	Inputmanager* mInput;
	AudioManager* mAudio;
	bool mVisible;
	bool mAnimating;
	int mScore;
	int mLives;

	AnimatedTexture* mDeathAnimatrion;

	Texture* mShip;
	float mfireRate = 0.2f;
	float mfireTimer;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	static const int MAX_BULLETS = 2;
	Bullet* mBullet[MAX_BULLETS];

private:
	void HandleMovement();
	void HandleFiring();
public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	void WasHit();

	void Update();

	void Render();
};

#endif
