#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 size) :Collider(ColliderType::Box)
{
	AddVert(0, Vector2(-0.5f * size.x, -0.5f * size.y));
	AddVert(1, Vector2(0.5f * size.x, -0.5f * size.y));
	AddVert(2, Vector2(-0.5f * size.x, 0.5f * size.y));
	AddVert(3, Vector2(0.5f * size.x, 0.5f * size.y));
	if (DEBUG_COLLIDERS)
	{
		
	}
}

BoxCollider::~BoxCollider()
{
	for (int i = 0; i < MAX_VERTS; i++)
	{
		delete mVerts[i];
		mVerts[i] = nullptr;
	}
}

Vector2 BoxCollider::GetFurthestPoint()
{
	Vector2 localPos = GetPos(GameEntity::local);

	int furthestIndex = 0;
	float dist = (localPos + mVerts[0]->GetPos(GameEntity::local)).MagnitureSqr();
	float otherDist = 0;

	for (int i = 1; i < MAX_VERTS; i++) {
		otherDist = (localPos + mVerts[i]->GetPos(GameEntity::local)).MagnitureSqr();
		if (otherDist > dist)
		{
			furthestIndex = i;
			dist = otherDist;
		}
	}
	return localPos + mVerts[furthestIndex]->GetPos(GameEntity::local);
}

Vector2 BoxCollider::GetVertexPos(int index)
{
	return mVerts[index]->GetPos();
}

void BoxCollider::AddVert(int index, Vector2 pos)
{
	mVerts[index] = new GameEntity(pos);
	mVerts[index]->Parent(this);
}
