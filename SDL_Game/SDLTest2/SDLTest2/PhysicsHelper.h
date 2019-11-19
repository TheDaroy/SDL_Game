#pragma once
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "MathHelper.h"
inline bool PointInPolygon(Vector2* verts, int vertCount, const Vector2& point)
{
	bool retVal = false;

	for (int i = 0, j = vertCount - 1; i < vertCount; j = i++ )
	{
		if ((verts[i].y >= point.y) != (verts[j].y >= point.y))
		{
			Vector2 vec1 = (verts[i] - verts[j]).Normalized();
			Vector2 proj = verts[j] + vec1 * Dot(point - verts[j], vec1);
			if (proj.x > point.x)
			{
				retVal = !retVal;
			}
		}
	}
	return retVal;
}

inline float PointToLineDistance(const Vector2& lineStart, const Vector2& lineEnd, const Vector2& point) {
	Vector2 slope = lineEnd - lineStart;
	float param = Clamp(Dot(point - lineStart, slope) / slope.MagnitureSqr(), 0, 1);

	Vector2 nearestPoint = lineStart + slope * param;
	
	return (point - nearestPoint).Magnitude();
}

inline bool CircleCircleCollision(CircleCollider* c1, CircleCollider* c2) {
	return (c1->GetPos() - c2->GetPos()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool BoxCircleCollision(BoxCollider* box, CircleCollider* circle)
{
	if (PointToLineDistance(box->GetVertexPos(0), box->GetVertexPos(1), circle->GetPos()) < circle->GetRadius() ||
		PointToLineDistance(box->GetVertexPos(0), box->GetVertexPos(2), circle->GetPos()) < circle->GetRadius() ||
		PointToLineDistance(box->GetVertexPos(2), box->GetVertexPos(3), circle->GetPos()) < circle->GetRadius() ||
		PointToLineDistance(box->GetVertexPos(3), box->GetVertexPos(1), circle->GetPos()) < circle->GetRadius())
	{
		return true;
	}
	Vector2 quad[4];
	quad[0] = box->GetVertexPos(0);
	quad[1] = box->GetVertexPos(1);
	quad[2] = box->GetVertexPos(3);
	quad[3] = box->GetVertexPos(2);
	if (PointInPolygon(quad, 4,circle->GetPos()))
	{
		return true;
	}
	return false;
}

inline bool ColliderColliderCheck(Collider* c1, Collider* c2) {

	if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Circle)
	{
		return CircleCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	}
	else if (c1->GetType() == Collider::ColliderType::Box && c2->GetType() == Collider::ColliderType::Circle)
	{
		return BoxCircleCollision(static_cast<BoxCollider*>(c1), static_cast<CircleCollider*>(c2));
	}
	else if (c2->GetType() == Collider::ColliderType::Box && c1->GetType() == Collider::ColliderType::Circle)
	{
		return BoxCircleCollision(static_cast<BoxCollider*>(c2), static_cast<CircleCollider*>(c1));
	}
}