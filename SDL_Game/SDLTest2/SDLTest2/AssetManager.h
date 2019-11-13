#pragma once
#include "Graphics.h"
#include <map>
#include <SDL_mixer.h>
namespace QuickSDL {
	class Assetmanager
	{
	private:
		static Assetmanager* sInstance;
		std::map<std::string, SDL_Texture*> mTextures;
		std::map<std::string, SDL_Texture*> mText;
		std::map<std::string, TTF_Font*>mFonts;
		std::map<std::string, Mix_Music*>mMusic;
		std::map<std::string, Mix_Chunk*>mSFX;

		Assetmanager();
		~Assetmanager();

		TTF_Font* GetFont(std::string FileName, int size);
	public:
		static Assetmanager* Instance();
		static void Release();

		SDL_Texture* GetTexture(std::string filename);
		SDL_Texture* GetText(std::string text, std::string fileName, int size, SDL_Color color);
		Mix_Music* GetMusic(std::string fileName);
		Mix_Chunk* GetSFX(std::string fileName);

	};
}