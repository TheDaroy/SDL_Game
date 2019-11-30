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


		mPlayer = new Player();
		mPlayer->Visible(true);
		test1 = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, 80));
		mTexture = new AnimatedTexture("SpaceShipSpriteSheet.png", 0, 0, 40, 38, 3, 1, AnimatedTexture::horizontal); // (path, Pos.x , Pos.y , W, H, frameCount, animSpeed, animDir)
		mTexture->Pos(Vector2(200, 200));


		mTexture2 = new Texture("", "Font1.ttf", 100, { 255,0,0 });
		mTexture2->Pos(Vector2(400, 400));
		mTexture2->Parent(test1);

		mTexture3 = new Texture("SpaceShipSpriteSheet.png", 0, 0, 40, 38);
		mTexture3->Pos(Vector2(100, 500));

		enemy1 = new EnemyTest();
		enemy1->Pos(Vector2(300,300));

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

		delete mTexture;
		mTexture = nullptr;
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
		//std::cout << enemy1->GetPos().x << "  " << enemy1->GetPos().y << std::endl;
		mTexture3->Translate(mTexture3->MoveTowards(mTexture->GetPos())  * 50 * mTimer->DeltaTime());
		mPlayer->Update();
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
		//mEnemyMgr->RenderEnemy();
		mPlayer->Render();
		mEnemyMgr->RenderEverything();
		mStars->Render();
		mScreenManager->Render();
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