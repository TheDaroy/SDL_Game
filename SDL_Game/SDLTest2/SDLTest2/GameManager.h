#pragma once


#include "InputManager.h"
#include "AudioManager.h"
#include "Timer.h"
#include "AnimatedTexture.h"
#include "Texture.h"
#include "EnemyManager.h"
#include "EnemyTest.h"
#include "ScreenManager.h"
#include "Player.h"
#include "PhysicsManager.h"
namespace QuickSDL {
	class GameManager
	{
	private:

		static GameManager* sInstance;
		const int frameRate = 60;

		bool mQuit;

		Graphics* mGraphics;
		Timer* mTimer;
		Assetmanager* mAssetManager;
		Inputmanager* mInputManager;
		AudioManager* mAudioMgr;
		EnemyManager* mEnemyMgr;
		ScreenManager* mScreenManager;
		BackgroundStars* mStars;
		PhysicsManager* mPhysMgt;
		GameEntity* test1;
		SDL_Event mEvent;

		GameManager();
		~GameManager();

		void EarlyUpdate();
		void Update();
		void LateUpdate();
		void Render();

	public:
		static GameManager* Instance();
		static void Release();
		void Run();




	};
}
