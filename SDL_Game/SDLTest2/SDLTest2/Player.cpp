#include "Player.h"

Player::Player()
{
	mTimer = Timer::Instance();
	mInput = Inputmanager::Instance();

	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 2;


	mShip = new Texture("BLABLABLA.PNG");
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
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
	}

	Vector2 pos = Pos(local);
	if (pos.x < mMoveBounds.x)
		pos.x = mMoveBounds.x;
	else if (pos.x > mMoveBounds.y)
		pos.x = mMoveBounds.y;

	Pos(pos)
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
		if (Active())
		{
			HandleMovement()
		}
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