#pragma once
#include <SDL.h>
#include <string.h>
#include "MathHelper.h"
namespace QuickSDL {
	class Inputmanager
	{
	private:
		static Inputmanager* sInstance;
		const Uint8* mKeyStates;
		Uint8* mPrevKeyState;
		int mKeyLength;

		Uint32 mPrevMouseState;
		Uint32 mMouseState;

		int mMouseXPos;
		int mMouseYPos;
		Inputmanager();
		~Inputmanager();
	public:

		enum MOUSE_BUTTON { left = 0, right, middle, back, forward };



		static Inputmanager* Instance();
		static void Release();

		bool KeyDown(SDL_Scancode scanCode);
		bool KeyPressed(SDL_Scancode scanCode);
		bool KeyReleased(SDL_Scancode scanCode);

		bool MouseButtonDown(MOUSE_BUTTON button);
		bool MouseButtonPressed(MOUSE_BUTTON button);
		bool MouseButtonReleased(MOUSE_BUTTON button);

		Vector2 MousePos();

		void Update();
		void UpdatePrevInput();
	};
}