#pragma once


#include "InputManager.h"
#include "AudioManager.h"
#include "Timer.h"
#include "AnimatedTexture.h"
#include "Texture.h"
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

		GameEntity* test1;
		SDL_Event mEvent;
		AnimatedTexture* mTexture;
		Texture* mTexture2;
		Texture* mTexture3;

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
