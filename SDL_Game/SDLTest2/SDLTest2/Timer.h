#pragma once
#include <SDL.h>
namespace QuickSDL{
	class Timer
	{
	private:

		static Timer* vInstance;
		unsigned int vStartTicks;
		unsigned int vElapsedTicks;
		float vDeltaTime;
		float vTimeScale;

		Timer();
		~Timer();

	public:

		static Timer* Instance();
		static void Release();

		void Reset();
		float DeltaTime();

		void TimeScale(float t);
		float TimeScale();
		void Update();

	};
}
