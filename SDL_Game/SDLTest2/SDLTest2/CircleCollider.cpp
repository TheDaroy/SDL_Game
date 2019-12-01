#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius, bool broadPhase) : Collider(ColliderType::Circle)
{
	mRadius = radius;
	if (DEBUG_COLLIDERS)
	{
		if (broadPhase)
		{
			SetDebugTexture(new Texture("Test.png"));
		}
		else
		{
			
		}
		mDebugTexture->Scale(VEC2_ONE * (radius * 2 / 100));
	}
}

CircleCollider::~CircleCollider()
{
}

Vector2 CircleCollider::GetFurthestPoint()
{
	return VEC2_RIGHT*(mRadius + GetPos(GameEntity::local).Magnitude());
}
float CircleCollider::GetRadius()
{
	return mRadius;
}


