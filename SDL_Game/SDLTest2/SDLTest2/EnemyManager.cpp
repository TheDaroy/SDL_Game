#include "EnemyManager.h"
#include "EnemyTest.h"
#include "Projectile.h"
#include <ctime>
EnemyManager* EnemyManager::sInstance = nullptr;
EnemyManager::EnemyManager()
{

}

EnemyManager::~EnemyManager()
{
	/*for (int i = 0; i < enemyList.size(); i++)
	{
		if (enemyList[i]->mActive)
		{
			delete enemyList[i];
		}
	}
	for (int i = 0; i < projectileList.size(); i++)
	{
		if (projectileList[i]->mActive)
		{
			delete projectileList[i];
		}
	}*/
}

EnemyManager* EnemyManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new EnemyManager();
	}
	return sInstance;
}

void EnemyManager::Release()
{
	

	delete sInstance;
	sInstance = nullptr;
	
}



void EnemyManager::AddToEnemyList(EnemyTest* entity)
{
	enemyList.push_back(entity);
}
void EnemyManager::AddToProjectileList(Projectile* entity)
{
	std::cout << projectileList.size() << std::endl;
	projectileList.push_back(entity);
}

void EnemyManager::RenderEverything()
{
	RenderEnemies();
	RenderProjectiles();

}

void EnemyManager::RenderEnemies()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (enemyList[i]->mActive)
		{
			enemyList[i]->Render();
		}
	}

}

void EnemyManager::RenderProjectiles()
{
	
	for (int i = 0; i < projectileList.size(); i++)
	{
		if (projectileList[i]->mActive)
		{
			projectileList[i]->Render();
		}
	}
}

void EnemyManager::UpdateAll()
{
	UpdateEnemies();
	UpdateProjectiles();
}

void EnemyManager::UpdateEnemies()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (enemyList[i]->mActive)
		{
			enemyList[i]->Update();
		}
	}
}

void EnemyManager::UpdateProjectiles()
{
	for (int i = 0; i < projectileList.size(); i++)
	{
		if (projectileList[i]->mActive)
		{
			projectileList[i]->Update();
		}
	}
}







Vector2 EnemyManager::newPath(EnemyTest* entity)
{
	bool findNR = true;
	Vector2 returnVector;
	while (findNR)
	{
		std::random_device seeder;
		std::mt19937 rng(seeder());
		std::uniform_int_distribution<int> genX(0, maxX);
		std::uniform_int_distribution<int> genY(0, maxY);
		int x = genX(seeder);
		
		int y = genY(seeder);
		
		returnVector.x = x;
		returnVector.y = y;
		findNR = false;
		
		for (int i = 1; i < enemyList.size(); i++)
		{
			if (returnVector.x == enemyList[i]->currentTargetVec.x && returnVector.y == enemyList[i]->currentTargetVec.y)
			{
				findNR = true;
			}
		}
	}
	std::cout << returnVector.x << "  " << returnVector.y << std::endl;
	return returnVector;
}
