#pragma once
#include "PhysEntity.h"
#include <bitset>
class PhysicsManager
{
public:
	enum class CollisionLayers {
		Friendly = 0,
		FriendlyProjectile,
		Hostile,
		HostileProjectile,
		Maxlayers
	};
	enum class CollisionFlags {
		None = 0x00,
		Friendly = 0x01,
		FriendlyProjectile = 0x02,
		Hostile = 0x04,
		HostileProjectiles = 0x08

	};

	static PhysicsManager* Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterEntity(PhysEntity* entity, CollisionLayers layer);
	void UnregisterEntity(unsigned long id);

	void Update();

private:
	static PhysicsManager* sInstance;
	std::vector<PhysEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::Maxlayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::Maxlayers)> mLayerMasks[static_cast<unsigned int> (CollisionLayers::Maxlayers)];
	unsigned long mLastId;

	PhysicsManager();
	~PhysicsManager();
	
};

inline PhysicsManager::CollisionFlags operator | (PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
	return static_cast <PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
	return static_cast <PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}
