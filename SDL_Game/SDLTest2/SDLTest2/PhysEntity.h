#pragma once
#include <vector>
#include "Collider.h"


class PhysEntity : public GameEntity
{
public:
	PhysEntity();
	virtual~PhysEntity();

	virtual void Render();
	unsigned long GetId();

protected:

	unsigned long mID;
	std::vector<Collider*> mColliders;
	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
	Collider* mBroadPhaseCollider;
};

