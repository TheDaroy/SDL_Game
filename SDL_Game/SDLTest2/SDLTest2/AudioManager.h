#pragma once
#include "AssetManager.h"
namespace QuickSDL {
	class AudioManager
	{
	public:



		static AudioManager* Instance();
		static void Release();

		void PlayMusic(std::string fileName, int loops = -1);
		void PauseMusic();
		void ResumeMusic();

		void PlaySFX(std::string fileName, int loops = 0, int channel = 0);

	private:
		AudioManager();
		~AudioManager();

		static AudioManager* sInstance;
		Assetmanager* mAssetMgr;


	};
}