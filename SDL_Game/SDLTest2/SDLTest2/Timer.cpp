#include "Timer.h"
namespace QuickSDL {
	Timer* Timer::vInstance = nullptr;

	Timer* Timer::Instance()
	{
		if (vInstance == nullptr)
		{
			vInstance = new Timer();
		}
		return vInstance;
	}


	Timer::Timer()
	{
		Reset();
		vTimeScale = 1.0f;
	}

	Timer::~Timer()
	{
	}



	void Timer::Release()
	{

		delete vInstance;
		vInstance = nullptr;
	}

	void Timer::Reset()
	{
		vStartTicks = SDL_GetTicks();
		vElapsedTicks = 0;
		vDeltaTime = 0.0f;
	}

	float Timer::DeltaTime()
	{
		return vDeltaTime;
	}

	void Timer::TimeScale(float t)
	{
		vTimeScale = t;
	}

	float Timer::TimeScale()
	{
		return vTimeScale;
	}

	void Timer::Update()
	{
		vElapsedTicks = SDL_GetTicks() - vStartTicks;
		vDeltaTime = vElapsedTicks * 0.001f;
	}
}