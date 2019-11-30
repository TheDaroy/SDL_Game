#include "Player.h"
#include "Projectile.h"
#include <iostream>
Player::Player()
{
	mTimer = Timer::Instance();
	mInput = Inputmanager::Instance();

	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 2;


	mShip = new Texture("SpaceShipSpriteSheet.png", 0, 0, 40, 38);
	mShip->Parent(this);
	
	mShip->Pos(VEC2_ZERO);

	mMoveSpeed = 100.0f;
	mMoveBounds = Vector2(0.9f, 800.0f);
}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;

	delete mShip;
	mShip = NULL;
}

void Player::HandleMovement()
{
	if (mInput->KeyDown(SDL_SCANCODE_DOWN))
	{
		Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime());
	}
	else if(mInput->KeyDown(SDL_SCANCODE_UP))
	{
		Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime() * -1);
	}

	if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime() * -1);
	}

	if (mInput->KeyDown(SDL_SCANCODE_SPACE))
	{
		new Projectile(GetPos(local), GetRotation(), 1000);	
	}
	std::cout << GetPos().x << " :  " << GetPos().y << std::endl;
	Vector2 pos = GetPos(world);
	if (pos.x < mMoveBounds.x)
		pos.x = mMoveBounds.x;
	else if (pos.x > mMoveBounds.y)
		pos.x = mMoveBounds.y;

	
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

void Player::Update()
{
	if (mAnimating)
	{

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

		}
		else
		{
			
			mShip->Render();
		}

	}
}