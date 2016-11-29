#pragma once
#include <chrono>

namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer();
		Timer(const Timer& aTimer) = delete;
		Timer& operator=(const Timer& aTimer) = delete;

		void Update();

		float GetDeltaTime() const;
		double GetTotalTime() const;
	private:
		float myDeltaTime;
		double myTotalTime;
		std::chrono::high_resolution_clock::time_point myCurrentFrameTime;
		std::chrono::high_resolution_clock::time_point myPreviousFrameTime;
	};
}

namespace CU = CommonUtilities;