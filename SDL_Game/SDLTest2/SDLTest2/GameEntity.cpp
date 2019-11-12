#include "GameEntity.h"
#include <iostream>

#pragma region Struct/De-Struct
GameEntity::GameEntity(float x, float y)
{
	mPos.x = x;
	mPos.y = y;

	mRotation = 0;

	mParent = nullptr;
	mScale = VEC2_ONE;
}

GameEntity::~GameEntity()
{
	mParent = nullptr;
}
#pragma endregion

#pragma region Pos
void GameEntity::Pos(Vector2 pos)
{
	mPos = pos;
}

Vector2 GameEntity::GetPos(SPACE space)
{
	
	if (space == local || mParent == NULL)
	{
		return mPos;
	}

	Vector2 parentScale = mParent->GetScale(world);
	Vector2 rotPos = RotateVector(mPos, mParent->GetRotation(local));

	return mParent->GetPos(world) + Vector2(rotPos.x * parentScale.x , rotPos.y * parentScale.y);
}

#pragma endregion

#pragma region Rotation

void GameEntity::Rotation(float rotation)
{
	mRotation = rotation;
	if (mRotation > 360.0f)
	{
		mRotation -= 360.0f;
	}

	if (mRotation < 0.0f)
	{
		mRotation += 360.0f;
	}
}

float GameEntity::GetRotation(SPACE space)
{
	if (space == local || mParent == nullptr)
	{
		return mRotation;
	}
	return mParent->GetRotation(world) + mRotation;
}
#pragma endregion



void GameEntity::Scale(Vector2 scale)
{
	mScale = scale;
}
Vector2 GameEntity::GetScale(SPACE space)
{
	if (space == local || mParent == nullptr)
	{
		return mScale;
	}
	Vector2 parentScale = mParent->GetScale(world);
	return Vector2(parentScale.x * mScale.x, parentScale.y * mScale.y);
}
#pragma region Active
void GameEntity::Active(bool active)
{
	mActive = active;
}

bool GameEntity::GetActive()
{
	return mActive;
}
#pragma endregion

#pragma region Parent

void GameEntity::Parent(GameEntity* parent)
{
	std::cout << parent << std::endl;
	mPos = GetPos(world) - parent->GetPos(world);
	mParent = parent;
}

GameEntity* GameEntity::Parent()
{
	return mParent;
}


#pragma endregion

void GameEntity::Translate(Vector2 vec)
{
	mPos += vec;
}

void GameEntity::Rotate(float amount)
{
	mRotation += amount;
}

#pragma region Update/Render
void GameEntity::Update()
{
}
void GameEntity::Render()
{
}
#pragma endregion

