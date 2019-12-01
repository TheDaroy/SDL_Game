#include "Player.h"
#include "Projectile.h"
#include "GameEntity.h"
#include <iostream>
Player::Player()
{
	mTimer = Timer::Instance();
	mInput = Inputmanager::Instance();
	mAudio = AudioManager::Instance();
	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 2;


	mShip = new Texture("SpaceShipSpriteSheet.png", 0, 0, 40, 38);
	mShip->Parent(this);
	
	mShip->Pos(VEC2_ZERO);

	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(0.9f, 800.0f);
	mDeathAnimatrion = new AnimatedTexture("playerexp.png", 0, 0, 125, 128, 4, 1.0f, AnimatedTexture::horizontal);
	mDeathAnimatrion->Parent(this);
	mDeathAnimatrion->Pos(VEC2_ZERO);
	mDeathAnimatrion->WrapMode(AnimatedTexture::once);

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullet[i] = new Bullet();
	}
}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;

	delete mShip;
	mShip = NULL;

	delete mDeathAnimatrion;
	mDeathAnimatrion = NULL;
}

void Player::HandleMovement()
{
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime()*-1 );
	}

	if (mInput->KeyDown(SDL_SCANCODE_UP))
	{
		Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime() * -1);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_DOWN))
	{
		Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime() );
	}

	/*if (mInput->KeyDown(SDL_SCANCODE_SPACE) && mfireTimer >= mfireRate)
	{
		new Projectile(GetPos(local), GetRotation(), 1000);	
		mfireTimer = 0;
	}*/
	std::cout << GetPos().x << " :  " << GetPos().y << std::endl;
	Vector2 pos = GetPos(world);
	if (pos.x < mMoveBounds.x)
		pos.x = mMoveBounds.x;
	else if (pos.x > mMoveBounds.y)
		pos.x = mMoveBounds.y;

	mfireTimer = mfireTimer + mTimer->DeltaTime();
	
}

void Player::HandleFiring()
{
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE))
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!mBullet[i]->GetActive())
			{
				mBullet[i]->Fire(GetPos());
				mAudio->PlaySFX("fire.waw");
				break;
			}
		}
	}
}

void Player::Visible(bool visible)
{
	mVisible = visible;
}

bool Player::IsAnimating()
{
	return mAnimating;
}

int Player::Score()
{
	return mScore;
}

int Player::Lives()
{
	return mLives;
}

void Player::AddScore(int change)
{
	mScore += change;
}
void Player::WasHit()
{
	mLives--;
	mDeathAnimatrion->ResetAnimation();
	mAnimating = true;
	mAudio->PlaySFX("Playdestroyed.waw");
}

void Player::Update()
{
	if (mAnimating)
	{
		mDeathAnimatrion->Update();
		mAnimating = mDeathAnimatrion->IsAnimating();
	}
	else
	{
			HandleMovement();
	}
}

void Player::Render()
{
	
	if (mVisible)
	{
		
		if (mAnimating)
		{
			mDeathAnimatrion->Render();
		}
		else
		{
			
			mShip->Render();
		}

	}
}