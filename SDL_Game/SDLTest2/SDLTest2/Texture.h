#pragma once
#include "GameEntity.h"
#include "AssetManager.h"
namespace QuickSDL {
#include <string>
	class Texture : public GameEntity
	{
	protected:

		SDL_Texture* mTexture;
		Graphics* mGraphics;

		int mWidth;
		int mHeight;

		bool mClipped;
		SDL_Rect mRenderRect;
		SDL_Rect mClippedRect;
	public:

		Texture(std::string filename);
		Texture(std::string filename, int x, int y, int w, int h);

		Texture(std::string text, std::string fontpath, int seize, SDL_Color color);
		~Texture();
		Vector2 ScaledDimensions();
		virtual void Render();
	};
}