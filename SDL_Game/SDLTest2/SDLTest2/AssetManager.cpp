#include "AssetManager.h"
#include <iostream>
Assetmanager* Assetmanager::sInstance = nullptr;
#pragma region Struct/De-Struct
Assetmanager::Assetmanager()
{

}

Assetmanager::~Assetmanager()
{
	for (auto textures : mTextures)
	{
		if (textures.second != nullptr)
		{
			SDL_DestroyTexture(textures.second);
		}
	}
	mTextures.clear();
	
	for (auto text : mText)
	{
		if (text.second != nullptr)
		{
			SDL_DestroyTexture(text.second);
		}
	}
	mText.clear();

	for (auto font : mFonts)
	{
		if (font.second != nullptr)
		{
			TTF_CloseFont(font.second);
		}
	}
	mFonts.clear();
}

#pragma endregion


Assetmanager* Assetmanager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new Assetmanager();
	}
	return sInstance;
}

void Assetmanager::Release()
{
	delete sInstance;
	sInstance = nullptr;
  
}

SDL_Texture* Assetmanager::GetTexture(std::string filename)
{
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + filename);
	if (mTextures[fullpath] == nullptr)
	{
		mTextures[fullpath] = Graphics::Instance()->LoadTexture(fullpath);
	}
	return mTextures[fullpath];
}

TTF_Font* Assetmanager::GetFont(std::string FileName, int size)
{
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + FileName);
	std::string key = fullpath + (char)size;

	if (mFonts[key] == nullptr)
	{
		mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);
		if (mFonts[key] == nullptr)
		{		
			std::cout << "Font Loading Error: " << FileName.c_str()<< " : "<<TTF_GetError << std::endl;


		}
	}
	return mFonts[key];
}

SDL_Texture* Assetmanager::GetText(std::string text, std::string fileName, int size, SDL_Color color)
{
	TTF_Font* font = GetFont(fileName, size);
	std::string key = text + fileName + (char)size;

	if (mText[key] == nullptr)
	{
		mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
	}
	return mText[key];
}

Mix_Music* Assetmanager::GetMusic(std::string fileName)
{
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + fileName);
	if (mMusic[fullpath] == nullptr)
	{
		mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());
		if (mMusic[fullpath] == nullptr)
		{
			std::cout << "Music Loading Error: " << fileName.c_str() <<" : " << Mix_GetError() << std::endl;
		}

	}
	return mMusic[fullpath];
}

Mix_Chunk* Assetmanager::GetSFX(std::string fileName)
{
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + fileName);
	if (mSFX[fullpath] == nullptr)
	{
		mSFX[fullpath] = Mix_LoadWAV(fullpath.c_str());

		if (mSFX[fullpath] == nullptr)
		{
			std::cout << "Music Loading Error: " << fileName.c_str()<< " : " << Mix_GetError() << std::endl;
		}

	}
	return mSFX[fullpath];
}
