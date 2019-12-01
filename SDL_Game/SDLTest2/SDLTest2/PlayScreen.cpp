#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mInput = Inputmanager::Instance();
	mAudio = AudioManager::Instance();

	mStars = BackgroundStars::Instance();
	mEnemyMgr = EnemyManager::Instance();
	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.9f, Graphics::Instance()->SCREEN_HEIGHT * 0.05f));

	mStartLabel = new Texture("START", "font1.ttf", 32, { 150, 0, 0 });
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, Graphics::Instance()->SCREEN_HEIGHT * 0.50f));

	mLevel = NULL;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mLevelStartMusicDelay = 8.0f;

	mPlayer = NULL;
}

PlayScreen::~PlayScreen() {
	mTimer = NULL;
	mInput = NULL;
	mStars = NULL;

	delete mSideBar;
	mSideBar = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;

	delete mPlayer;
	mPlayer = NULL;

}

void PlayScreen::StartNextLevel() {
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	mSideBar->SetLevel(mCurrentStage);

	delete mLevel;
	mLevel = new Level(mCurrentStage, mSideBar, mPlayer);
}

void PlayScreen::StartNewGame() {
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, Graphics::Instance()->SCREEN_HEIGHT * 0.8f));
	mPlayer->Active(false);


	mEnemy = new EnemyTest();
	mEnemy->Parent(this);
	mEnemy->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, Graphics::Instance()->SCREEN_HEIGHT * 0.2f));

	mStars->Scroll(false);
	mSideBar->SetHighScore(30000);
	mSideBar->SetShips(mPlayer->Lives());
	mSideBar->SetPlayerScore(mPlayer->Score());

	mGameStarted = false;
	mAudio->PlayMusic("gamestart.wav", 0);
	mCurrentStage = 0;
}

void PlayScreen::Update() {
	if (mGameStarted) {
		if (!mLevelStarted) {
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay) {
				StartNextLevel();
			}
		}
	}
	else {
		mLevelStartMusicTimer += mTimer->DeltaTime();
		if (mLevelStartMusicTimer >= mLevelStartMusicDelay) {
			mGameStarted = true;
		}
	}

	if (mGameStarted) {
		if (mCurrentStage > 0) {
			mSideBar->Update();
		}
		if (mLevelStarted) {
			mLevel->Update();
		}
		mPlayer->Update();
	}
}

void PlayScreen::Render() {
	mSideBar->Render();

	if (!mGameStarted) {
		mStartLabel->Render();
	}

	if (mGameStarted) {
		if (mLevelStarted) {
			mLevel->Render();
		}
		mPlayer->Render();
		mEnemyMgr->RenderEverything();

	}
}