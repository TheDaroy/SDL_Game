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
	PhysicsManager();
	~PhysicsManager();

private:
	static PhysicsManager* sInstance;
	std::vector<PhysEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::Maxlayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::Maxlayers)> mLayerMasks[static_cast<unsigned int> (CollisionLayers::Maxlayers)];
	unb
};

