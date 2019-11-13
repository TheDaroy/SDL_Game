#include "InputManager.h"
namespace QuickSDL {
	Inputmanager* Inputmanager::sInstance = nullptr;
#pragma region Struct/ De-struct
	Inputmanager::Inputmanager()
	{
		mKeyStates = SDL_GetKeyboardState(&mKeyLength);
		mPrevKeyState = new Uint8[mKeyLength];
		memcpy(mPrevKeyState, mKeyStates, mKeyLength);
	}

	Inputmanager::~Inputmanager()
	{
		delete[]mPrevKeyState;
		mPrevKeyState = nullptr;
	}
#pragma endregion


	Inputmanager* Inputmanager::Instance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new Inputmanager();

		}
		return sInstance;
	}

	void Inputmanager::Release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	bool Inputmanager::KeyDown(SDL_Scancode scanCode)
	{
		return mKeyStates[scanCode];
	}

	bool Inputmanager::KeyPressed(SDL_Scancode scanCode)
	{
		return !mPrevKeyState[scanCode] && mKeyStates[scanCode];
	}

	bool Inputmanager::KeyReleased(SDL_Scancode scanCode)
	{
		return mPrevKeyState[scanCode] && !mKeyStates[scanCode];
	}

	Vector2 Inputmanager::MousePos()
	{
		return Vector2((float)mMouseXPos, (float)mMouseYPos);
	}
	bool Inputmanager::MouseButtonDown(MOUSE_BUTTON button)
	{
		Uint32 mask = 0;

		switch (button)
		{
		case Inputmanager::left:
			mask = SDL_BUTTON_LMASK;
			break;
		case Inputmanager::right:
			mask = SDL_BUTTON_RMASK;
			break;
		case Inputmanager::middle:
			mask = SDL_BUTTON_MMASK;
			break;
		case Inputmanager::back:
			mask = SDL_BUTTON_X1MASK;
			break;
		case Inputmanager::forward:
			mask = SDL_BUTTON_X2MASK;
			break;

		}
		return (mMouseState & mask);
	}

	bool Inputmanager::MouseButtonPressed(MOUSE_BUTTON button)
	{
		Uint32 mask = 0;

		switch (button)
		{
		case Inputmanager::left:
			mask = SDL_BUTTON_LMASK;
			break;
		case Inputmanager::right:
			mask = SDL_BUTTON_RMASK;
			break;
		case Inputmanager::middle:
			mask = SDL_BUTTON_MMASK;
			break;
		case Inputmanager::back:
			mask = SDL_BUTTON_X1MASK;
			break;
		case Inputmanager::forward:
			mask = SDL_BUTTON_X2MASK;
			break;

		}
		return !(mPrevMouseState & mask) && (mMouseState & mask);
	}

	bool Inputmanager::MouseButtonReleased(MOUSE_BUTTON button)
	{
		Uint32 mask = 0;

		switch (button)
		{
		case Inputmanager::left:
			mask = SDL_BUTTON_LMASK;
			break;
		case Inputmanager::right:
			mask = SDL_BUTTON_RMASK;
			break;
		case Inputmanager::middle:
			mask = SDL_BUTTON_MMASK;
			break;
		case Inputmanager::back:
			mask = SDL_BUTTON_X1MASK;
			break;
		case Inputmanager::forward:
			mask = SDL_BUTTON_X2MASK;
			break;

		}
		return (mPrevMouseState & mask) && !(mMouseState & mask);
	}




	void Inputmanager::Update()
	{
		mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
	}

	void Inputmanager::UpdatePrevInput()
	{
		memcpy(mPrevKeyState, mKeyStates, mKeyLength);
		mPrevMouseState = mMouseState;
	}
}
