#include "Timer.h"

namespace CommonUtilities
{
	Timer::Timer()
	{
		myTotalTime = 0;
		myPreviousFrameTime = std::chrono::high_resolution_clock::now();
	}

	void Timer::Update()
	{
		myCurrentFrameTime = std::chrono::high_resolution_clock::now();

		auto floatDur = myCurrentFrameTime - myPreviousFrameTime;
		auto sec = std::chrono::duration_cast<std::chrono::duration<float>>(floatDur);

		myDeltaTime = sec.count();
		myTotalTime += myDeltaTime;

		myPreviousFrameTime = std::chrono::high_resolution_clock::now();
	}
	float Timer::GetDeltaTime() const
	{
		return myDeltaTime;
	}
	double Timer::GetTotalTime() const
	{
		return myTotalTime;
	}
}
