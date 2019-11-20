#include "StartScreen.h"

StartScreen::StartScreen() {

	mTimer = Timer::Instance();
	mInput = Inputmanager::Instance();

	//Top Bar Entities 
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 70.0f));
	mPlayerOne = new Texture("1UP", "font1.ttf", 32, { 200, 0 ,0 });
	mPlayerTwo = new Texture("2UP", "font1.ttf", 32, { 200, 0 ,0 });
	mHiScore = new Texture("HI-SCORE", "font1.ttf", 32, { 200, 0 ,0 });

	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHiScore->Parent(mTopBar);

	mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
	mPlayerTwo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
	mHiScore->Pos(VEC2_ZERO);

	mTopBar->Parent(this);

	//Logo Entities
	mLogo = new Texture("Spritesheet.png", 0, 0, 360, 180);
	mAnimatedLogo = new AnimatedTexture("Spritesheet.png", 0, 0, 360, 180, 5, 0.2f, AnimatedTexture::vertical);

	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.35f));
	mAnimatedLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.35f));

	mLogo->Parent(this);
	mAnimatedLogo->Parent(this);

	//Play Mode Entities
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.6f));
	mOnePlayerMode = new Texture("1 Player", "font1.ttf", 32, { 230, 230, 230 });
	mTwoPlayerMode = new Texture("2 Players", "font1.ttf", 32, { 230, 230, 230 });
	mCursor = new Texture("Cursor.png");

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mOnePlayerMode->Pos(Vector2(0.0f, -30.0f));
	mTwoPlayerMode->Pos(Vector2(0.0f, 30.0f));
	mCursor->Pos(Vector2(-170.0f, -35.0f));

	mPlayModes->Parent(this);

	mCursorStartPos = Vector2(-170.0f, -35.0f);
	mCursorOffset = Vector2(0.0f, 70.0f);
	mSelectedMode = 0;

	//Bottom Bar Entities
	mBotBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.75f));
	mNamco = new Texture("NAMCOT", "font1.ttf", 36, { 200, 0 ,0 });
	mDates = new Texture("1981 1985 NAMCO LTD.", "font1.ttf", 32, { 230, 230, 230 });
	mRights = new Texture("ALL RIGHTS RESERVED", "font1.ttf", 32, { 230, 230, 230 });

	mNamco->Parent(mBotBar);
	mDates->Parent(mBotBar);
	mRights->Parent(mBotBar);

	mNamco->Pos(VEC2_ZERO);
	mDates->Pos(Vector2(0.0f, 50.0f));
	mRights->Pos(Vector2(0.0f, 100.0f));

	mBotBar->Parent(this);

	//Screen Animation Variables
	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VEC2_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);

	mStars = BackgroundStars::Instance();
	mStars->Scroll(true);
}

StartScreen::~StartScreen() {
	//Freeing Top Bar Entities
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayerOne;
	mPlayerOne = NULL;
	delete mPlayerTwo;
	mPlayerTwo = NULL;
	delete mHiScore;
	mHiScore = NULL;

	//Freeing Logo Entities
	delete mLogo;
	mLogo = NULL;
	delete mAnimatedLogo;
	mAnimatedLogo = NULL;

	//Freeing Play Mode Entities
	delete mPlayModes;
	mPlayModes = NULL;
	delete mOnePlayerMode;
	mOnePlayerMode = NULL;
	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;
	delete mCursor;
	mCursor = NULL;

	//Freeing Bottom Bar Entities
	delete mBotBar;
	mBotBar = NULL;
	delete mNamco;
	mNamco = NULL;
	delete mDates;
	mDates = NULL;
	delete mRights;
	mRights = NULL;
}

void StartScreen::ChangeSelectedMode(int change) {
	mSelectedMode += change;

	if (mSelectedMode < 0) {
		mSelectedMode = 1;
	}
	else if (mSelectedMode > 1) {
		mSelectedMode = 0;
	}

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedMode);
}

void StartScreen::Update() {
	if (!mAnimationDone) {
		mAnimationTimer += mTimer->DeltaTime();
		Pos(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
			mStars->Scroll(false);
		}

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP)) {
			mAnimationTimer = mAnimationTotalTime;
		}
	}
	else {
		mAnimatedLogo->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
			ChangeSelectedMode(1);
		}
		else if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
			ChangeSelectedMode(-1);
		}
	}
}

void StartScreen::Render() {
	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHiScore->Render();

	if (!mAnimationDone) {
		mLogo->Render();
	}
	else {
		mAnimatedLogo->Render();
	}

	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mCursor->Render();

	mNamco->Render();
	mDates->Render();
	mRights->Render();

}