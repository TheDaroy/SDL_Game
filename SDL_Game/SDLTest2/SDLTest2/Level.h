#ifndef _LEVEL_H
#define _LEVEL_H

#include "InputManager.h"
#include "PlaySideBar.h"
#include "BackgroundStars.h"
#include "Player.h"

class Level : public GameEntity {
private:
	Timer* mTimer;
	PlaySideBar* mSideBar;
	BackgroundStars* mStars;

	int mStage;
	bool mStageStarted;

	float mLabelTimer;

	Texture* mStageLabel;
	Scoreboard* mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Player* mPlayer;

private:
	void StartStage();

public:
	Level(int stage, PlaySideBar* sideBar, Player* player);
	~Level();

	void Update();
	void Render();

};

#endif // !_LEVEL_H
