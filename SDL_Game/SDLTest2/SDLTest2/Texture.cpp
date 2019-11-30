#include "Texture.h"
#include <iostream>
namespace QuickSDL {
#pragma region Struct/De-Struct
	Texture::Texture(std::string filename)
	{
		mGraphics = Graphics::Instance();
		mTexture = Assetmanager::Instance()->GetTexture(filename);
		SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
		mClipped = false;
		mRenderRect.w = mWidth;
		mRenderRect.h = mHeight;
	}

	Texture::Texture(std::string filename, int x, int y, int w, int h)
	{
		mGraphics = Graphics::Instance();
		mTexture = Assetmanager::Instance()->GetTexture(filename);

		mClipped = true;
		mWidth = w;
		mHeight = h;

		mRenderRect.w = mWidth;
		mRenderRect.h = mHeight;

		mClippedRect.x = x;
		mClippedRect.y = y;
		mClippedRect.w = mWidth;
		mClippedRect.h = mHeight;
	}

	Texture::Texture(std::string text, std::string fontpath, int seize, SDL_Color color)
	{
		std::cout << text << fontpath << std::endl;
		mGraphics = Graphics::Instance();
		mTexture = Assetmanager::Instance()->GetText(text, fontpath, seize, color);

		mClipped = false;

		SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);

		mRenderRect.w = mWidth;
		mRenderRect.h = mHeight;
	}

	Texture::~Texture()
	{

		mTexture = nullptr;
		mGraphics = nullptr;

	}
	Vector2 Texture::ScaledDimensions()
	{
		Vector2 scaledDimensions = GetScale();
		scaledDimensions.x *= mWidth;
		scaledDimensions.y *= mHeight;

		return scaledDimensions;
	}
#pragma endregion



	void Texture::Render()
	{
		Vector2 pos = GetPos(world);
		Vector2 scale = GetScale(world);

		mRenderRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
		mRenderRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
		mRenderRect.w = (int)(mWidth * scale.x);
		mRenderRect.h = (int)(mHeight * scale.y);

		mGraphics->DrawTexture(mTexture, (mClipped) ? &mClippedRect : NULL, &mRenderRect, GetRotation(world));
	}
}