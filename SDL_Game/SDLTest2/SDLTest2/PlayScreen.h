#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H

#include "InputManager.h"
#include "BackgroundStars.h"
#include "PlaySideBar.h"
#include "Level.h"
#include "Player.h"
#include "EnemyTest.h"
#include "EnemyManager.h"
class PlayScreen : public GameEntity {
private:
	Timer* mTimer;
	Inputmanager* mInput;
	AudioManager* mAudio;

	BackgroundStars* mStars;
	PlaySideBar* mSideBar;

	Texture* mStartLabel;
	float mLevelStartTimer;
	float mLevelStartDelay;
	float mLevelStartMusicTimer;
	float mLevelStartMusicDelay;

	bool mGameStarted;

	Level* mLevel;
	bool mLevelStarted;
	int mCurrentStage;
	EnemyManager* mEnemyMgr;
	Player* mPlayer;
	EnemyTest* mEnemy;
private:
	void StartNextLevel();


public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void Update();
	void Render();
};
#endif // !_PLAYSCREEN_H
