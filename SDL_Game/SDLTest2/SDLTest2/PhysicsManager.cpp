#include "PhysicsManager.h"
#include "PhysEntity.h"



#pragma region construct/de-struct
PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}
#pragma endregion

PhysicsManager* PhysicsManager::sInstance = nullptr;
PhysicsManager* PhysicsManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new PhysicsManager();
	}
	return sInstance;
}

void PhysicsManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
		
}

void PhysicsManager::SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags)
{
	mLayerMasks[static_cast<unsigned int>(layer)] = std::bitset<static_cast<unsigned int>(CollisionLayers::Maxlayers)>(static_cast<unsigned int>(flags));
}

unsigned long PhysicsManager::RegisterEntity(PhysEntity* entity, CollisionLayers layer)
{
	mCollisionLayers[static_cast<unsigned int>(layer)].push_back(entity);
	mLastId++;
	return mLastId;
}

void PhysicsManager::UnregisterEntity(unsigned long id)
{
	bool found = false;
	for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::Maxlayers) && !found; i++)
	{
		for (int j = 0; j < mCollisionLayers[i].size()&& !found; j++)
		{
			if (mCollisionLayers[i][j]->GetId() == id)
			{
				mCollisionLayers[i].erase(mCollisionLayers[i].begin() + j);
				found = true;
			}
		}
	}
}

void PhysicsManager::Update()
{
}


