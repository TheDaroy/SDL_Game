#include "GameManager.h"
#include <iostream>

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
	
	mTexture = new AnimatedTexture("SpriteSheet.png", 204, 45, 40, 38, 4, 0.5f, AnimatedTexture::horizontal); // (path, Pos.x , Pos.y , W, H, frameCount, animSpeed, animDir)
	mTexture->Pos(Vector2(100, 200));
	

	mTexture2 = new Texture("Hello World", "Font.ttf", 100, { 255,0,0 });
	mTexture2->Pos(Vector2(500, 200));	
	mTexture->Scale(Vector2(0.5f, 0.5f));
	mTexture2->Parent(mTexture);
}

GameManager::~GameManager()
{

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
		while (SDL_PollEvent(&mEvent) !=0)
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
