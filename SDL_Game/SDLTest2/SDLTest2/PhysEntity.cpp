#include "PhysEntity.h"



PhysEntity::PhysEntity()
{
}

PhysEntity::~PhysEntity()
{
	for (int i = 0; i< mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}
	mColliders.clear();
}

void PhysEntity::Render()
{
}


void PhysEntity::AddCollider(Collider* collider, Vector2 localPos)
{
	
	collider->Parent(this);
}
