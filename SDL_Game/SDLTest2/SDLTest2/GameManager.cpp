#include "GameManager.h"

#include <iostream>
namespace QuickSDL {
	GameManager* GameManager::sInstance = nullptr;

	GameManager::GameManager()
	{
		mQuit = false;
		mGraphics = Graphics::Instance();

		if (!Graphics::Instance())
		{
			mQuit = true;
		}
		mTimer = Timer::Instance();

		mAssetManager = Assetmanager::Instance();
		mInputManager = Inputmanager::Instance();
		mAudioMgr = AudioManager::Instance();
		mEnemyMgr = EnemyManager::Instance();
		mPhysMgt = PhysicsManager::Instance();

		
		mPhysMgt->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, PhysicsManager::CollisionFlags::Hostile | PhysicsManager::CollisionFlags::HostileProjectiles);
		

		

		

		mStars = BackgroundStars::Instance();
		mScreenManager = ScreenManager::Instance();
	}

	GameManager::~GameManager()
	{
		BackgroundStars::Release();
		mStars = nullptr;

		ScreenManager::Release();
		mScreenManager = nullptr;

		Assetmanager::Release();
		mAssetManager = nullptr;

		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		Inputmanager::Release();
		mInputManager = nullptr;

		AudioManager::Release();
		mAudioMgr = nullptr;

		
	}

	void GameManager::EarlyUpdate()
	{
		mInputManager->Update();
	}

	void GameManager::Update() //Inputs Etc
	{
		mStars->Update();
		mScreenManager->Update();
		mEnemyMgr->UpdateAll();
		
				
		
		
	}

	void GameManager::LateUpdate()
	{
		mInputManager->UpdatePrevInput();
		mTimer->Reset();
	}

	void GameManager::Render()
	{
		mGraphics->ClearBackBuffer();
		
		
		mStars->Render();
		mScreenManager->Render();
	
		mGraphics->Render();
	}

	GameManager* GameManager::Instance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new GameManager();
		}
		return sInstance;
	}

	void GameManager::Release()
	{
		delete sInstance;
		sInstance = nullptr;


	}

	void GameManager::Run()
	{
		while (!mQuit)
		{
			mTimer->Update();
			while (SDL_PollEvent(&mEvent) != 0)
			{
				if (mEvent.type == SDL_QUIT)
				{
					mQuit = true;
				}

			}
			if (mTimer->DeltaTime() >= 1.0f / frameRate)
			{
				EarlyUpdate();
				Update();
				LateUpdate();
				Render();
			}
		}
	}
}