#include "Graphics.h"
#include <iostream>
namespace QuickSDL {
	Graphics* Graphics::sInstance = nullptr;
	bool Graphics::sInitialized = false;
#pragma region Struct/De-Struct
	Graphics::Graphics()
	{
		mBackBuffer = nullptr;
		sInitialized = init();
	}

	Graphics::~Graphics()
	{
		SDL_DestroyWindow(mainWindow);
		mainWindow = nullptr;

		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
#pragma endregion

#pragma region Instance/Release/Initialized
	Graphics* Graphics::Instance()
	{
		if (sInstance == NULL)
		{
			sInstance = new Graphics();
		}
		return sInstance;
	}

	void Graphics::Release()
	{
		delete sInstance;
		sInstance = NULL;

		sInitialized = false;
	}

	bool Graphics::Initialized()
	{
		return sInitialized;
	}

#pragma endregion


	SDL_Texture* Graphics::LoadTexture(std::string path)
	{
		SDL_Texture* texture = nullptr;
		SDL_Surface* surface = IMG_Load(path.c_str());
		if (surface == nullptr)
		{
			std::cout << "IMG Load Error: " << IMG_GetError() << std::endl;
			return texture;
		}

		texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (texture == nullptr)
		{
			std::cout << "Texture Load Error: " << SDL_GetError() << std::endl;
			return texture;
		}
		SDL_FreeSurface(surface);
		return texture;
	}

	SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color)
	{
		std::cout << text << font << std::endl;
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

		if (surface == NULL)
		{
			std::cout << "Text Render Error: " << TTF_GetError << std::endl;
			return NULL;
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (tex == NULL)
		{
			std::cout << "Texture Creation Error: " << SDL_GetError << std::endl;
			return NULL;
		}
		SDL_FreeSurface(surface);

		return tex;
	}

	void Graphics::ClearBackBuffer()
	{
		SDL_RenderClear(mRenderer);
	}

	void Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(mRenderer, texture, clip, rend, angle, NULL, flip);
	}

	void Graphics::Render()
	{
		SDL_RenderPresent(mRenderer);
	}



	bool Graphics::init()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			std::cout << "SDL Initialization Error: " << SDL_GetError() << std::endl;
			return false;
		}

		mainWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (mainWindow == NULL)
		{
			std::cout << "Window Initialization Error: " << SDL_GetError() << std::endl;
			return false;
		}
		mRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);


		if (mRenderer == nullptr)
		{
			std::cout << "Renderer Initialization Error: " << SDL_GetError() << std::endl;
			return false;
		}
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);



		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags))
		{
			std::cout << "IMG Initialization Error: " << IMG_GetError() << std::endl;
			return false;
		}


		if (TTF_Init() == -1)
		{
			std::cout << "TTF Initialization Error: " << TTF_GetError() << std::endl;
			return false;
		}

		mBackBuffer = SDL_GetWindowSurface(mainWindow);
		return true;
	}
}