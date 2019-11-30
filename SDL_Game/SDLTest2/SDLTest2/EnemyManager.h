#pragma once

#include "Timer.h"
#include "MathHelper.h"
#include <vector>
#include <iostream>
#include <random>
using namespace QuickSDL;
class EnemyTest;
class Projectile;
class EnemyManager
{
public:
	
	EnemyManager();
	~EnemyManager();

	static EnemyManager* Instance();
	static void Release();
	void AddToEnemyList(EnemyTest* entity);
	void AddToProjectileList(Projectile* entity);

	void RenderEverything();
	void RenderEnemies();
	void RenderProjectiles();

	void UpdateAll();
	void UpdateEnemies();
	void UpdateProjectiles();
	
	
	Vector2 newPath(EnemyTest* entity);
private:
	static EnemyManager* sInstance;
	std::vector<EnemyTest*> enemyList;
	std::vector<Projectile*> projectileList;
	unsigned int maxX = 800;
	unsigned int maxY = 400;
	
};