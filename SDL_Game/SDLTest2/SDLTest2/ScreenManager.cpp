#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance() {
	if (sInstance == NULL) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager() {
	mInput = Inputmanager::Instance();

	mBackgroundStars = BackgroundStars::Instance();
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager() {
	mInput = NULL;

	BackgroundStars::Release();
	mBackgroundStars = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;
}

void ScreenManager::Update() {
	mBackgroundStars->Update();

	switch (mCurrentScreen) {
	case ScreenManager::start:
		mStartScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			mCurrentScreen = play;
			mStartScreen->ResetAnimation();
		}
		break;

	case ScreenManager::play:

		mPlayScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mCurrentScreen = start;
		}

		break;
	}
	
}

void ScreenManager::Render() {
	mBackgroundStars->Render();

	switch (mCurrentScreen)
	{
	case ScreenManager::start:
		mStartScreen->Render();

		break;

	case play:
		mPlayScreen->Render();

		break;
	}
}