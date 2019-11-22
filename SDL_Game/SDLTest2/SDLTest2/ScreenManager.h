#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H

#include "StartScreen.h"

class ScreenManager {
private:
	enum SCREENS { start, play };
	
	static ScreenManager* sInstance;

	Inputmanager* mInput;

	BackgroundStars* mBackgroundStars;
	StartScreen* mStartScreen;

	SCREENS mCurrentScreen;

public:
	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};

#endif // !_SCREENMANAGER_H
