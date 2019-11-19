#include "GameEntity.h"
#include <iostream>
namespace QuickSDL {
#pragma region Struct/De-Struct
	GameEntity::GameEntity(Vector2 pos)
	{
		mPos = pos;
		mRotation = 0;
		mActive = true;
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

		if (space == local || mParent == nullptr)
		{
			return mPos;
		}

		GameEntity* parent = mParent;
		Vector2 finalPos = mPos, parentScale = VEC2_ZERO;

		do 
		{
			Vector2 parentScale = mParent->GetScale(local);
			finalPos = RotateVector(Vector2(finalPos.x * parentScale.x, finalPos.y * parentScale.y), parent->GetRotation(local));
			finalPos += parent->GetPos(local);
			parent = parent->Parent();
		} while (parent);

		

		return finalPos;
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
		Vector2 scale = mParent->GetScale(world);
		scale.x *= mScale.x;
		scale.y *= mScale.y;

		return scale;
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
		

		if (parent == nullptr)
		{
			
			mPos = GetPos(world);
			mRotation = GetRotation(world);
			mScale = GetScale(world);
		}
		else
		{
			
			if (parent != nullptr)
			{
				Parent(nullptr);
			}
			Vector2 parentScale = parent->GetScale(world);

			mPos = RotateVector(GetPos(world) - parent->GetPos(world), -parent->GetRotation(world));
			mPos.x /= parentScale.x;
			mPos.y /= parentScale.y;

			mRotation -= parent->GetRotation(world);
			mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
		}
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
}

