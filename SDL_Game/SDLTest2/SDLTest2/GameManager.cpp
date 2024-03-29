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
		mPhysMgr =  PhysicsManager::Instance();

		mPhysMgr->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, PhysicsManager::CollisionFlags::Hostile | PhysicsManager::CollisionFlags::HostileProjectiles);
		mPhysMgr->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectile, PhysicsManager::CollisionFlags::Hostile);
		mPhysMgr->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile, PhysicsManager::CollisionFlags::Friendly | PhysicsManager::CollisionFlags::FriendlyProjectile);
		mPhysMgr->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectile, PhysicsManager::CollisionFlags::Friendly);

		test1 = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, 80));
		mTexture = new AnimatedTexture("SpaceShipSpriteSheet.png", 0, 0, 40, 38, 3, 1, AnimatedTexture::horizontal); // (path, Pos.x , Pos.y , W, H, frameCount, animSpeed, animDir)
		mTexture->Pos(Vector2(100, 200));


		mTexture2 = new Texture("Hello World", "Font1.ttf", 100, { 255,0,0 });
		mTexture2->Pos(Vector2(500, 200));
		//mTexture2->Parent(test1);

		mTexture3 = new Texture("SpaceShipSpriteSheet.png", 0, 0, 40, 38);
		mTexture3->Pos(Vector2(200, 200));

	}

	GameManager::~GameManager()
	{
		PhysicsManager::Release();
		mPhysMgr = nullptr;

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

		delete mTexture;
		mTexture = nullptr;
	}

	void GameManager::EarlyUpdate()
	{
		mInputManager->Update();
	}

	void GameManager::Update() //Inputs Etc
	{
		if (mInputManager->KeyPressed(SDL_SCANCODE_W))
		{
			mAudioMgr->PlaySFX("VictorySound.wav");
			std::cout << "W Pressed" << std::endl;
		}
		if (mInputManager->KeyReleased(SDL_SCANCODE_W))
		{
			mAudioMgr->PlaySFX("VictorySound.wav");
		}
		if (mInputManager->MouseButtonPressed(Inputmanager::middle))
		{
			std::cout << "M Mouse Pressed" << std::endl;
		}
		if (mInputManager->MouseButtonPressed(Inputmanager::back))
		{
			std::cout << "Back Mouse Pressed" << std::endl;
		}
		if (mInputManager->MouseButtonPressed(Inputmanager::left))
		{
			std::cout << "Left Mouse Pressed" << std::endl;
		}


		mTexture->Update();
		mTexture->Rotate(10 * mTimer->DeltaTime());
	}

	void GameManager::LateUpdate()
	{
		mInputManager->UpdatePrevInput();
		mTimer->Reset();
	}

	void GameManager::Render()
	{
		mGraphics->ClearBackBuffer();
		mTexture->Render();
		mTexture2->Render();
		mTexture3->Render();
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